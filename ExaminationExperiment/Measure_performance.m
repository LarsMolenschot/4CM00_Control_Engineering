e = Data.signals.e;
<<<<<<< Updated upstream
a = Data.signals.a;
y = Data.signals.y;
e_max = max(abs(e))
e_rms = rms_error(e)
fs = Data.settings.fs

t = (0:1/fs:(length(e)-1)*(1/fs));
figure; hold on;
% n = (1:length(e));
accel_region = (abs(sign(a))).*e_max;
area(t,accel_region ,'FaceColor',"r",'FaceAlpha',0.4,'EdgeColor','none')
area(t,-accel_region ,'FaceColor',"r",'FaceAlpha',0.4,'EdgeColor','none')
stairs(t,e,'Color','k');
 
%stairs(e);
% plot(0.01*(1-sign(abs(a))));
=======
% a = Data.signals.a;
y = Data.signals.y;
e_max = max(abs(e))
e_rms = rms_error(e)
scale = 0.0001;

figure; stairs(e);
hold on;
plot(0.01*(1-sign(abs(a))));
>>>>>>> Stashed changes
%hold on; stairs(a.*scale);
% figure; stairs(y); 
% hold on; stairs(a);

Fres = 0.1
fs = Data.settings.fs;
nfft = fs/Fres;
window = hanning(nfft);
noverlap = floor(nfft/2);
[PSD, f] = pwelch(e,window,noverlap,nfft,fs,"onesided"); %PSD
figure; plot(f,PSD);
yscale log;
xscale log;
grid on;


%%
<<<<<<< Updated upstream
Trun = 11
=======
Trun = 120
>>>>>>> Stashed changes
N_samples = Trun*Fs; %measurement size per duration(samples)
T_terminate = 5;
Fres = 0.1


Exercise = "ProtoLab_setup_45_2410";
<<<<<<< Updated upstream
Measurement = "Setpoint_11s_13p5Hz_N52p9";
=======
Measurement = "Setpoint_11s_13p5Hz";
>>>>>>> Stashed changes
SampleFreq = "fs_" + Fs + "_Hz";

ModelName = "Hardware_Performance_run";
[success, y,e,a] = StartSignalMeasurement(p,N_samples,T_terminate,ModelName);
if(~success)
    error("No measurement made!");
end
e_max = max(abs(e))
e_rms = rms_error(e)

nfft = Fs/Fres;
window = hanning(nfft);
noverlap = floor(nfft/2);
[PSD, f] = pwelch(e,window,noverlap,nfft,fs,"onesided"); %PSD
figure; plot(f,PSD);
yscale log;
xscale log;
grid on;

Path = "PerformanceMeasurements/"  ...
        + Exercise ...
        + "/" + SampleFreq;

measurementName = Measurement + "_T" + Trun + "_S" + N_samples;
saveMeasurement(...
struct("runtime", Trun, "fs", Fs, "samples", N_samples), ...%settings    
struct("a", a,"e",e,"y",y), ... %signals
struct("PSD",PSD,"f",f,"e_max",e_max,"e_rms",e_rms),...
Path + '/PerformanceData/'+ measurementName);

figure; hold on; grid on;
n = (1:length(e));
accel_region = (abs(sign(a))).*e_max;
<<<<<<< Updated upstream
area(n,accel_region,'FaceColor',"r",'FaceAlpha',0.4,'EdgeColor','none')
area(n,-accel_region,'FaceColor',"r",'FaceAlpha',0.4,'EdgeColor','none')
stairs(n,e,'Color','k');
=======
area(n,accel_region*1000 ,'FaceColor',"r",'FaceAlpha',0.4,'EdgeColor','none')
area(n,-accel_region*1000 ,'FaceColor',"r",'FaceAlpha',0.4,'EdgeColor','none')
stairs(e);
>>>>>>> Stashed changes

figure; stairs(y); 
hold on; stairs(a);
grid on;

function e_rms = rms_error(e)
%RMS_ERROR  Compute RMS value of an error signal.
%
%   e_rms = RMS_ERROR(e)
%
%   Inputs:
%       e - error signal vector (difference between ref and measurement)
%
%   Output:
%       e_rms - root mean square error
%
%   Example:
%       e = [0.1, -0.2, 0.05, 0.15];
%       e_rms = rms_error(e)

    % Ensure it's a vector
    e = e(:);

    % Compute discrete-time RMS
    e_rms = sqrt(mean(e.^2));
end