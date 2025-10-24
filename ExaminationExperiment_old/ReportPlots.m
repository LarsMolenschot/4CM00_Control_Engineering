clear all;
close all;
clc
%% System identification
%close all; clear all;
%raw data
Data_frf = GetMyData(1,"HardwareMeasurements/ProtoLab_setup_45_2110/fs_4000_hz/measured_signals/MeasurementOrder"); 
Data_frf = Data_frf.Data;

runtime = Data_frf.settings.runtime;
fs = Data_frf.settings.fs;
N = Data_frf.settings.samples;
signals = unpackSignals(Data_frf,["d","y","u","e","r"]);

[nfft, noverlap, window] = setFres(1,fs);
[f1, H1, S1, Coh1, C_est1, L_est1] = threePoint(signals.d,signals.e,signals.u,window,noverlap,nfft,fs);

[nfft, noverlap, window] = setFres(0.1,fs);
[f2, H2, S2, Coh2, C_est2, L_est2] = threePoint(signals.d,signals.e,signals.u,window,noverlap,nfft,fs);

figHandle = mybode(f1,H1,Coh1,"FRF Non-colocated system identification");
figHandle = mybode(f2,H2,Coh2,[],figHandle);

legend(figHandle.H_tile)
legend(figHandle.Coh_tile,["C_{ps}_1", "C_{s}_1","C_{ps}_2", "C_{s}_2"])

saveas(figHandle.fig,"Figures/FRF_System_Identification",'png')

function [nfft, noverlap, window] = setFres(Fres, fs)
    nfft = floor(fs/Fres);
    noverlap = floor(nfft/2);
    window = hann(nfft);
end
%% FFW tuning low bandwidth stabilizing controller (lead/lag -lowpass), challenging trajectory
% Store trajectory data (simulation)
%===== Motion profile =====%
FFW_setpoint = load("Setpoints/PlottingData/FFW_setpoint");
accel = FFW_setpoint.setpointData.a;
vel = FFW_setpoint.setpointData.v;
pos = FFW_setpoint.setpointData.s;
t = FFW_setpoint.setpointData.t;

fig_setpoint_FFW = figure;
hold on; grid on;
plot(t,accel,'Color','r','LineWidth',1);
plot(t,vel,'Color','b','LineWidth',1);
plot(t,pos,'Color','k','LineWidth',1);
xlabel('Time [s]','Interpreter','latex')
legend(["Acceleration $[rad/s^2]$", "Velocity $[rad/s]$", "Position $[rad]$"],'Interpreter','latex', ...
    'Location','southeastoutside');
title("FFW trajectory");
saveas(fig_setpoint_FFW,"Figures/FFW_setpoint",'png');

%close all; clear all;
Path = "FFW_Data/ProtoLab_setup_45_2110/fs_4000_hz/FFW_Data/MeasurementOrder";
Data_ = GetMyData(1,Path); Data_ = Data_.Data;
Data_fc = GetMyData(2,Path); Data_fc = Data_fc.Data;
Data_fv = GetMyData(3,Path); Data_fv = Data_fv.Data;
Data_fa = GetMyData(10,Path); Data_fa = Data_fa.Data;

%% ===== Correct alingment =====%
fs= Data_.settings.fs;
PlotLength = 20000-1;
Offset = 1;

for i = 1 : 2
    start_ = nthStateSwitch(sign(Data_.signals.a_ref),4);
    start_fc = nthStateSwitch(sign(Data_fc.signals.a_ref),7);
    start_fv = nthStateSwitch(sign(Data_fv.signals.a_ref),3);
    start_fa = nthStateSwitch(sign(Data_fa.signals.a_ref),5);
    
    start = start_fa;
    PlotData = Data_fa.signals; 
    
    figure; plot(PlotData.e); title("Pick best region"); %pick best region
    figure; plot(sign(PlotData.a_ref)); title("match samples");%use to match samples
    n_start = start-Offset;
    n_end = start+PlotLength-Offset;
    len = n_end-n_start;
    % figure; plot(sign(PlotData.a_ref(n_start:n_end))); title("found region"); %use to match samples
    % figure; plot(flip(sign(PlotData.a_ref(n_start:n_end))));("match samples flip"); %use to match samples
    endSamples = nthStateSwitch(flip(sign(PlotData.a_ref(n_start:n_end))),1); %find reversed
    Offset = floor((endSamples+Offset)/2);
end
%% ===== Plotting =====%
fig_ffw = figure();
hold on; grid on;
t = (0:1/fs:PlotLength*(1/fs));
plot(t,Data_.signals.e(start_-Offset:start_+PlotLength-Offset));
plot(t,Data_fc.signals.e(start_fc-Offset:start_fc+PlotLength-Offset));
plot(t,Data_fv.signals.e(start_fv-Offset:start_fv+PlotLength-Offset));
StaticOffset = 0;%Data_fa.signals.e(start_fa-Offset);
plot(t,Data_fa.signals.e(start_fa-Offset:start_fa+PlotLength-Offset)-StaticOffset);
yline(1.1,'LineStyle','--');
yline(-1.1,'LineStyle','--');
legend(["No FFW", "K_f_c" , "K_f_v" ,"K_f_a"],'Location','southeast');
xlabel('$Time [s]$','Interpreter','latex');
ylabel('$\theta [rad]$','Interpreter','latex');
title('Feed forward tuning - error profile');

saveas(fig_ffw,"Figures/FFW_tuning",'png');
fig_ffw_error = figure;
plot(t,Data_fa.signals.e(start_fa-Offset:start_fa+PlotLength-Offset).*1000);
hold on;
StaticOffset = Data_fa.signals.e(start_fa-Offset);
e_noOffset = Data_fa.signals.e(start_fa-Offset:start_fa+PlotLength-Offset)-StaticOffset;
plot(t,e_noOffset.*1000); %remove static offset
e_max_noOffset = max(abs(e_noOffset));
e_max = max(abs(Data_fa.signals.e(start_fa-Offset:start_fa+PlotLength-Offset)));

grid on;
xlabel('$Time [s]$','Interpreter','latex')
ylabel('$\theta [mrad]$','Interpreter','latex')
title('Feed forward tuning - final error')
legend(["Static offset, e_{max} = " + round(e_max*10^3,2) + " [mrad]", ...
    "No static offset, e_{max} = " + round(e_max_noOffset*10^3,2) + " [mrad]"], ...
    'Location','southeast')

saveas(fig_ffw_error,"Figures/FFW_final_error",'png');


%% Performance
%===== Motion profile 11s =====%
Performance_setpoint_11s = load("Setpoints/PlottingData/Performance_setpoint_11s");
accel = Performance_setpoint_11s.setpointData.a;
vel = Performance_setpoint_11s.setpointData.v;
pos = Performance_setpoint_11s.setpointData.s;
t = Performance_setpoint_11s.setpointData.t;

fig_setpoint_performance = figure;
hold on; grid on;
plot(t,accel,'Color','r','LineWidth',1);
plot(t,vel,'Color','b','LineWidth',1);
plot(t,pos,'Color','k','LineWidth',1);
xlabel('Time [s]','Interpreter','latex')
legend(["Acceleration $[rad/s^2]$", "Velocity $[rad/s]$", "Position $[rad]$"],'Interpreter','latex', ...
    'Location','southeastoutside')
title("Trajectory 11 sec")
saveas(fig_setpoint_performance,"Figures/Performance_setpoint_11s",'png');

%% ===== error 11s =====%
Path = "PerformanceMeasurements/ProtoLab_setup_45_2110/fs_4000_hz/PerformanceData/MeasurementOrder";
Data_perf_11 = GetMyData(7,Path); Data_perf_11 = Data_perf_11.Data;

figure; plot(Data_perf_11.signals.e)


e = Data_perf_11.signals.e;
e_max = max(abs(e))
e_rms = sqrt(mean(e.^2))

a = Data_perf_11.signals.a;

%% ===== Correct alingment =====%
fs = 4000;
PlotTime = 13;
offsetTime = floor((PlotTime - 11)/2);
PlotLength = PlotTime*fs-1;
offset = offsetTime*fs-1;

figure; plot(sign(a)); title("Match samples"); %use to match samples
for i = 1 : 2
    start = nthStateSwitch(sign(a),2);
    
    n_start = start-offset;
    n_end = start+PlotLength-offset;
    len = n_end-n_start;
    % figure; plot(sign(a(n_start:n_end))) %use to match samples
    % figure; plot(flip(sign(a(n_start:n_end)))) %use to match samples
    endSamples = nthStateSwitch(flip(sign(a(n_start:n_end))),1); %find reversed
    offset = floor((endSamples+offset)/2);
end
start_11 = start-offset;
end_11 = start+PlotLength-offset;

len = end_11-start_11;
figure; plot(sign(a(start_11:end_11))); title("Fitted data")

t = (-(offset+1)*1/fs:1/fs:(PlotLength-offset-1)*1/fs);

fig_perf_11 = figure;
hold on; grid on;

accel_window = (abs(sign(a(start_11:end_11)))).*e_max*1;
% plot(t,vel_window.*1000,'LineWidth',2,'Color','r');
area(t,accel_window*1000 ,'FaceColor',"r",'FaceAlpha',0.4,'EdgeColor','none')
area(t,-accel_window*1000 ,'FaceColor',"r",'FaceAlpha',0.4,'EdgeColor','none')
plot(t,e(start_11:end_11).*1000,'Color','k');
title("Error")
ylabel('Error [mrad]','Interpreter','latex');
xlabel('Time [s]','Interpreter','latex');
ax = gca;
ax.XTick = min(ax.XLim):1:max(ax.XLim);
legend("","acceleration phase","Error")
ax = gca;
msg = {
    "e_{max} = " + round(e_max * 1000,2) + " [mrad]"
    "e_{rms} = " + round(e_rms * 1000,2) + " [mrad]"
};
text(ax, 0.9, 0.6, msg, ...
    ...
    'Units','normalized', ...
    'HorizontalAlignment','left', ...
    'VerticalAlignment','middle', ...
    'FontSize', 14);

saveas(fig_perf_11,"Figures/Performance_Error_11s",'png')
%% PSD 11s
Fres = 0.1;
nfft = fs/Fres;
window = hanning(nfft);
noverlap = floor(nfft/2);
[PSD, f] = pwelch(e,window,noverlap,nfft,fs,"onesided"); %PSD
fig_PSD_11s = figure; 
plot(f,PSD);
yscale log;
xscale log;
grid on;
xlabel('Freq [Hz]');
ylabel('rad^2/Hz');
title("PSD of the error");
saveas(fig_PSD_11s,"Figures/Performance_PSD_11s",'png');


%% 

function idx = nthStateSwitch(vec, n)
% nthStateSwitch Find the index of the n-th state switch in a vector
% containing -1, 0, and 1.
%
%   idx = nthStateSwitch(vec, n)
%
%   Inputs:
%     vec : vector containing states (-1, 0, 1)
%     n   : which switch to find (positive = from start, negative = from end)
%
%   Output:
%     idx : index of the element *after* the n-th switch.
%           Returns NaN if fewer than |n| switches exist.

    % Input validation
    if ~isvector(vec) || ~all(ismember(vec, [-1 0 1]))
        error('Input must be a vector containing only -1, 0, and 1.');
    end

    % Find indices where state changes (non-zero diff)
    switches = find(diff(vec) ~= 0) + 1;

    if isempty(switches)
        idx = NaN;
        return;
    end

    % Select n-th (or -n-th) switch
    if n > 0
        if n <= numel(switches)
            idx = switches(n);
        else
            idx = NaN;
        end
    elseif n < 0
        if abs(n) <= numel(switches)
            idx = switches(end + n + 1);
        else
            idx = NaN;
        end
    else
        error('n must be nonzero.');
    end
end
%% Store setpoint data
setpointData = struct()
setpointData.a = a.signals.values;
setpointData.v = v.signals.values;
setpointData.s = r.signals.values;
setpointData.t = a.time;

 if(false)
    name = "Performance_setpoint_11s"
    save("Setpoints/PlottingData/"+name,"setpointData")
 end

fig_setpoint_performance = figure;
hold on; grid on;
plot(setpointData.t,setpointData.a,'Color','r','LineWidth',1);
plot(setpointData.t,setpointData.v,'Color','b','LineWidth',1);
plot(setpointData.t,setpointData.s,'Color','k','LineWidth',1);
xlabel('Time [s]','Interpreter','latex')
legend(["Acceleration $[rad/s^2]$", "Velocity $[rad/s]$", "Position $[rad]$"],'Interpreter','latex', ...
    'Location','southeastoutside')


