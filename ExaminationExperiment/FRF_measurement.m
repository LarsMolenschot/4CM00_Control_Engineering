%testing
%fs can not be modified during runtime, manually set fs in simulink!!
%Fs = 4000 %defined in simulink
%Ts = 1/Fs %defined in simulink
%%

Exercise = "Static";
SampleFreq = "fs_" + 4000 + "_Hz";

Path = "HardwareMeasurements/"  ...
        + Exercise ...
        + "/" + SampleFreq 

Path1 = "HardwareMeasurements/"  ...
        + "Exercise_2" ...
        + "/" + SampleFreq 
Path6 = "HardwareMeasurements/"  ...
        + "Protolab_vel_6" ...
        + "/" + SampleFreq 
%% 

L = Data.calculatedData.L
H = Data.calculatedData.H
f = Data.calculatedData.f
c = Data.calculatedData.C   
mybode(f,H,c,"Protolab")
%%
% ------------------- Controller (Run before simulink) ----------------------------%
s = tf('s');
Kp = 10;
Kd = 0.1;

f_filt = 200;
b_filt = 0.7;

C_pd = (Kp + s*Kd);
C_filter = (1)/((1/(2*pi*f_filt)^2)*s^2+((2*b_filt)/(2*pi*f_filt))*s+1);

C_total = C_pd * C_filter;
%%
% Automated measurements per Fs
% Set the required sample frequency manually in the simulink file before running on the hardware!!
include_processing = 1 % if set to 0, only the measurements are taken and stored

% --------------------- Set before measurement ----------------------%
%Measurment Name
Exercise = "ControllerChange";
Measurement = "static_FRF_openLoop_P10";
SampleFreq = "fs_" + Fs + "_Hz";

Path = "HardwareMeasurements/"  ...
        + Exercise ...
        + "/" + SampleFreq

N_measurements = 1
Trun = [120] %measurement durations
frames = [120] %amount of frames
variance = '0.1';

%Measurement Type (1: Closed_loop, 0: Open_loop)
measurementType = 0;


% ------------------ Calculated by program --------------------------%

if(isempty(C_total))
    error("Controller not defined");
end

samples = Trun*Fs; %measurement size per duration(samples)
nfft = zeros(length(Trun),length(frames));
for i = 1 : length(Trun)
    nfft(i,:) = Trun(i)./frames*Fs;
    for j = 1 : length(nfft(i,:))
        if (nfft(i,j) - floor(nfft(i,j))) > 0 %not an integer valeu
         warning("nfft("+i+","+j+") is not an integer value: " + nfft(i,j));
         nfft(i,j) = floor(nfft(i,j));
         warning("flooring to nfft(" + i + "," + j + ") = " + nfft(i,j));
        end
    end
end

Fres = Fs./nfft;

%start running the automated measurements for n cycles
for cycles = 1 : N_measurements
    %Measuring, take 1 measurement of the longest FRF time
    [d_raw,y_raw,u_raw,e_raw,r_raw] = StartFRFMeasurement(p,samples(end),variance,measurementType,'Hardware_FRF_setup');
    
    %Store raw data
    measurementName = "Cycle" + cycles + "_" + Measurement + "_T" + Trun(end) + "_S" + samples(end);
    saveMeasurement(...
    struct("runtime", Trun(end), "fs", Fs, "samples", samples(end)), ...%settings
    struct("r", r_raw, "d",d_raw,"u",u_raw,"e",e_raw,"y",y_raw), ... %signals
    [], ...%calculatedData
    Path +'/measured_signals/'+ measurementName);
    
    for i = 1 : length(Trun)
        %Split measurement in smaller chunkes of samples
        d = d_raw(1:samples(i));
        y = y_raw(1:samples(i));
        u = u_raw(1:samples(i));
        e = e_raw(1:samples(i));
        r = r_raw(1:samples(i));
    
        %store seperated measurements
        measurementName = "Cycle" + cycles + "_" + Measurement + "_T" + Trun(i) + "_S" + samples(i);
        saveMeasurement(...
        struct("runtime", Trun(i), "fs", Fs, "samples", samples(i)), ...%settings
        struct("r", r, "d",d,"u",u,"e",e,"y",y), ... %signals
        [], ...%calculatedData
        Path +'/seperated_measured_signals/'+ measurementName);
    
        %processing
        if(include_processing ~= 0)
            for j = 1 : length(frames)
                noverlap = floor(nfft(i,j)/2);
                window = hann(nfft(i,j));
    
                switch (measurementType)
                    case 1 % Closed_loop
                        % 2-point method
                        [f, H, S, L, Coh, C_resp] = twoPoint(d, u, r, C_total, window, noverlap, nfft(i,j), Fs);
                        
                        %store 2-point data
                        measurementName = "Cycle" + cycles + "_" + Measurement + "_T" + Trun(i) + "_Fr" + frames(j) + "_S" + samples(i) + "_nfft" + nfft(i,j);
                        saveMeasurement(...
                        struct("runtime", Trun(i), "fs", Fs, "samples", samples(i),"nfft", nfft(i,j),"noverlap", noverlap,"window", window, "fres", Fres(i,j), "C_res", C_resp), ...%settings    
                        struct("r", r, "d",d,"u",u,"e",e,"y",y), ... %signals
                        struct("f",f,"H",H,"S",S, "L", L,"C",Coh), ...%calculatedData
                        Path + '/processed_signals/2_point/'+ measurementName);
        
                        % 3-point method
                        [f, H, S, C, C_est, L_est] = threePoint(d,e,u,window,noverlap,nfft(i,j),Fs);
        
                        %store 3-point data
                        measurementName = "Cycle" + cycles + "_" + Measurement + "_T" + Trun(i) + "_Fr" + frames(j) + "_S" + samples(i) + "_nfft" + nfft(i,j);
                        saveMeasurement(...
                        struct("runtime", Trun(i), "fs", Fs, "samples", samples(i),"nfft", nfft(i,j),"noverlap", noverlap,"window", window, "fres", Fres(i,j),"C_res", C_est), ...%settings    
                        struct("r", r, "d",d,"u",u,"e",e,"y",y), ... %signals
                        struct("f",f,"H",H,"S",S,"L",L_est, "C",C), ...%calculatedData
                        Path + '/processed_signals/3_point/'+ measurementName);
                    otherwise % Open_loop
                        %H = y/u
                        [H_est,f_est] = tfestimate(u,y,window,noverlap,nfft(i,j),Fs);
                        [Ch, ~] = mscohere(u,y,window,noverlap,nfft(i,j),Fs);

                        %store open loop frf data
                        measurementName = "Cycle" + cycles + "_" + Measurement + "_T" + Trun(i) + "_Fr" + frames(j) + "_S" + samples(i) + "_nfft" + nfft(i,j);
                        saveMeasurement(...
                        struct("runtime", Trun(i), "fs", Fs, "samples", samples(i),"nfft", nfft(i,j),"noverlap", noverlap,"window", window, "fres", Fres(i,j),"C_res", C_est), ...%settings    
                        struct("r", r, "d",d,"u",u,"e",e,"y",y), ... %signals
                        struct("f",f_est,"H",H_est,"S",[],"L",[], "C",Ch), ...%calculatedData
                        Path + '/processed_signals/Open_loop/'+ measurementName);

                end
            end
        end
    end
end