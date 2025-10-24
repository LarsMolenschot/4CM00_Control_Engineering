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

L = Data.calculatedData.L
H = Data.calculatedData.H
f = Data.calculatedData.f
c = Data.calculatedData.C   
mybode(f,[H,L],c,"H vs L")
 PlotProcessedData([ ...
    GetProcessedData(Path,"3_point",1) ...
    GetProcessedData(Path,"3_point",2) ...
    
     ], ...
     "Protolab")
%% 
L = Data.calculatedData.L;
H = Data.calculatedData.H;
f = Data.calculatedData.f;
Coh = Data.calculatedData.Coh;  

mybode(f,H,Coh,replace(Data.FileName,'_',''))
%%
% ------------------- Controller (Run before simulink) ----------------------------%
s = tf('s');
Kp = 0.02;
Kd = 0.002;

f_filt = 200;
b_filt = 0.7;

C_pd = (Kp + s*Kd);
C_filter = (1)/((1/(2*pi*f_filt)^2)*s^2+((2*b_filt)/(2*pi*f_filt))*s+1);

C_total = C_pd * C_filter
%%
% Automated measurements per Fs
% Set the required sample frequency manually in the simulink file before running on the hardware!!
include_processing = 1 % if set to 0, only the measurements are taken and stored

% --------------------- Set before measurement ----------------------%
%Measurment Name
Exercise = "ProtoLab_setup_45_2410";
Measurement = "SanityCheck";
SampleFreq = "fs_" + Fs + "_Hz";

Path = "HardwareMeasurements/"  ...
        + Exercise ...
        + "/" + SampleFreq

N_measurements = 1
Trun = [120] %measurement durations
Fres = [0.5] %amount of frames
variance = '0.1';

%Measurement Type (1: Closed_loop, 0: Open_loop)
measurementType = 1;
model = 'Hardware_FRF_setup';

% ------------------ Calculated by program --------------------------%

if(isempty(C_total))
    error("Controller not defined");
end

samples = Trun*Fs; %measurement size per duration(samples)
nfft = floor(Fs./Fres);

[d_raw,y_raw,u_raw,e_raw,r_raw] = StartFRFMeasurement(p,samples,variance,model);
    
%Store raw data
measurementName = Measurement + "_T" + Trun + "_S" + samples;
saveMeasurement(...
struct("runtime", Trun, "fs", Fs, "samples", samples), ...%settings
struct("r", r_raw, "d",d_raw,"u",u_raw,"e",e_raw,"y",y_raw), ... %signals
[], ...%calculatedData
Path +'/measured_signals/'+ measurementName);
    
%Split measurement in smaller chunkes of samples
d = d_raw(1:samples);
y = y_raw(1:samples);
u = u_raw(1:samples);
e = e_raw(1:samples);
r = r_raw(1:samples);

%store seperated measurements
measurementName = Measurement + "_T" + Trun + "_S" + samples;
saveMeasurement(...
struct("runtime", Trun, "fs", Fs, "samples", samples), ...%settings
struct("r", r, "d",d,"u",u,"e",e,"y",y), ... %signals
[], ...%calculatedData
Path +'/seperated_measured_signals/'+ measurementName);
    
%processing
if(include_processing ~= 0)
        noverlap = floor(nfft/2);
        window = hann(nfft);

        switch (measurementType)
            case 1 % Closed_loop
                % 2-point method
                [f, H, S, L, Coh, C_resp] = twoPoint(d, u, r, C_total, window, noverlap, nfft, Fs);
                
                %store 2-point data
                measurementName = Measurement + "_T" + Trun + "_Fr" + replace(num2str(Fres),'.','p') + "_S" + samples + "_nfft" + nfft;
                saveMeasurement(...
                struct("runtime", Trun, "fs", Fs, "samples", samples,"nfft", nfft,"noverlap", noverlap,"window", window, "fres", Fres, "C_res", C_resp), ...%settings    
                struct("r", r, "d",d,"u",u,"e",e,"y",y), ... %signals
                struct("f",f,"H",H,"S",S, "L", L,"C",Coh), ...%calculatedData
                Path + '/processed_signals/2_point/'+ measurementName);

                % 3-point method
                [f, H, S, C, C_est, L_est] = threePoint(d,e,u,window,noverlap,nfft,Fs);

                %store 3-point data
                measurementName = Measurement + "_T" + Trun + "_Fr" + frames + "_S" + samples + "_nfft" + nfft;
                saveMeasurement(...
                struct("runtime", Trun, "fs", Fs, "samples", samples,"nfft", nfft,"noverlap", noverlap,"window", window, "fres", Fres,"C_res", C_est), ...%settings    
                struct("r", r, "d",d,"u",u,"e",e,"y",y), ... %signals
                struct("f",f,"H",H,"S",S,"L",L_est, "C",C), ...%calculatedData
                Path + '/processed_signals/3_point/'+ measurementName);
            otherwise % Open_loop
                %H = y/u
                [H_est,f_est] = tfestimate(u,y,window,noverlap,nfft,Fs);
                [Ch, ~] = mscohere(u,y,window,noverlap,nfft,Fs);

                %store open loop frf data
                measurementName = Measurement + "_T" + Trun + "_Fr" + frames + "_S" + samples + "_nfft" + nfft;
                saveMeasurement(...
                struct("runtime", Trun, "fs", Fs, "samples", samples,"nfft", nfft,"noverlap", noverlap,"window", window, "fres", Fres,"C_res", C_est), ...%settings    
                struct("r", r, "d",d,"u",u,"e",e,"y",y), ... %signals
                struct("f",f_est,"H",H_est,"S",[],"L",[], "C",Ch), ...%calculatedData
                Path + '/processed_signals/Open_loop/'+ measurementName);
    end
end
