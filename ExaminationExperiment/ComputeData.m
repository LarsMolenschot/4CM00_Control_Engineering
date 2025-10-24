
Root = "HardwareMeasurements";
Setup = "ProtoLab_setup_45_2110";
SampleFreq = "fs_" + 4000 + "_Hz";
SignalType = "manual_processed_signals";
Type = "Open_loop"
ChildFolder = "MeasurementOrder";


Path = Root + "/" + Setup + "/" +  SampleFreq + "/" +  SignalType + "/" + Type + "/" +  ChildFolder 
Data = GetMyData(1,Path);
Data = Data.Data;

L = Data.calculatedData.L;
H = Data.calculatedData.H;
f = Data.calculatedData.f;
Coh = Data.calculatedData.Coh;  

ControllerData = load("Controllers/Load_Controller_V2_lowpass_13_5Hz")
ControllerData = ControllerData.shapeit_data;
H_model = squeeze(freqresp(ControllerData.C_tf,2*pi.*f));
mybode(f,[H,H_model],Coh,replace(Data.FileName,'_',''))
%% 
L = Data.calculatedData.L;
H = Data.calculatedData.H;
f = Data.calculatedData.f;
Coh = Data.calculatedData.Coh;  

mybode(f,H,Coh,replace(Data.FileName,'_',''))
%%
%Measurment Name
Root = "HardwareMeasurements";
Setup = "ProtoLab_setup_45_2410";
SampleFreq = "fs_" + 4000 + "_Hz";
SignalType = "measured_signals";
ChildFolder = "MeasurementOrder";
MeasurementName = "ClosedLoop";

Number = 1

Path = Root + "/" + Setup + "/" +  SampleFreq + "/" +  SignalType + "/" +  ChildFolder 
%Measurement Type (1: Closed_loop, 0: Open_loop)
measurementType = 1;

%Open loop settings
signalNames = ["d","y","u","e","r"];
inName = "d";
outName = "u";


% ------------------ FRF setttings --------------------------%
Fres = 0.5;

RawData = GetMyData(Number,Path);
RawData = RawData.Data;
Trun = RawData.settings.runtime;
Fs = RawData.settings.fs;
nfft = floor(Fs/Fres);
samples = Trun*Fs;

vars = struct();
for X = signalNames
    if(isfield(RawData.signals,X))
        vars.(X) = RawData.signals.(X);
        if(inName == X) 
            in = vars.(X);
        end
        if(outName == X)
            out = vars.(X);
        end
    end
end

% ------------------ Calculated by program --------------------------%
Path = Root + "/" + Setup + "/" +  SampleFreq

%processing
noverlap = floor(nfft/2);
window = hann(nfft);

switch (measurementType)
    case 1 % Closed_loop
        if(measurementType == 1 && exist('C_total','var'))
        % 2-point method
        [f, H, S, L, Coh, C_resp] = twoPoint(vars.d, vars.u, vars.r, C_total, window, noverlap, nfft, Fs);
        
        %store 2-point data
        measurementName = MeasurementName + "_T" + Trun + "_Fr" + replace(num2str(Fres),'.','p') + "_S" + samples + "_nfft" + nfft;
        saveMeasurement(...
        struct("runtime", Trun, "fs", Fs, "samples", samples,"nfft", nfft,"noverlap", noverlap,"window", window, "fres", Fres, "C_res", C_resp), ...%settings    
        struct("r", vars.r, "d",vars.d,"u",vars.u,"e",vars.e,"y",vars.y), ... %signals
        struct("f",f,"H",H,"S",S, "L", L,"Coh",Coh, "C",C_resp), ...%calculatedData
        Path + '/manual_processed_signals/2_point/'+ measurementName);
        end
        % 3-point method
        [f, H, S, Coh, C_est, L_est] = threePoint(vars.d,vars.e,vars.u,window,noverlap,nfft,Fs);

        %store 3-point data
        measurementName = MeasurementName + "_T" + Trun + "_Fr" + replace(num2str(Fres),'.','p') + "_S" + samples + "_nfft" + nfft;
        saveMeasurement(...
        struct("runtime", Trun, "fs", Fs, "samples", samples,"nfft", nfft,"noverlap", noverlap,"window", window, "fres", Fres,"C_res", C_est), ...%settings    
        struct("r", vars.r, "d",vars.d,"u",vars.u,"e",vars.e,"y",vars.y), ... %signals
        struct("f",f,"H",H,"S",S,"L",L_est, "Coh",Coh, "C",C_est), ...%calculatedData
        Path + '/manual_processed_signals/3_point/'+ measurementName);
    otherwise % Open_loop
        %H = out/in
        [H_est,f_est] = tfestimate(in,out,window,noverlap,nfft,Fs);
        [Ch, ~] = mscohere(in,out,window,noverlap,nfft,Fs);

        %store open loop frf data
        measurementName = MeasurementName + "_T" + Trun + "_Fr" + replace(num2str(Fres),'.','p') + "_S" + samples + "_nfft" + nfft;
        saveMeasurement(...
        struct("runtime", Trun, "fs", Fs, "samples", samples,"nfft", nfft,"noverlap", noverlap,"window", window, "fres", Fres), ...%settings    
        struct("r", vars.r, "d",vars.d,"u",vars.u,"e",vars.e,"y",vars.y), ... %signals
        struct("f",f_est,"H",H_est,"S",[],"L",[], "Coh",Ch, "C",[]), ...%calculatedData
        Path + '/manual_processed_signals/Open_loop/'+ measurementName);
end