clear all;
close all;
clc
%% Figure setup
AxisFontSize = 50;
TitleFontSize = 50;
LegendFontSize = 24;

GeneralLineWidth = 2;
%% System identification
%close all; clear all;
%raw data
Data_frf = GetMyData(1,"HardwareMeasurements/ProtoLab_setup_45_2410/fs_4000_hz/measured_signals/MeasurementOrder"); 
Data_frf = Data_frf.Data;
Data_frf.FileName
runtime = Data_frf.settings.runtime;
fs = Data_frf.settings.fs;
N = Data_frf.settings.samples;
signals = unpackSignals(Data_frf,["d","y","u","e","r"]);


[nfft, noverlap, window] = setFres(0.5,fs);
[f1, H1, S1, Coh1, C_est1, L_est1] = threePoint(signals.d,signals.e,signals.u,window,noverlap,nfft,fs);


figHandle = mybode(f1,H1,[],"FRF Non-collocated system identification");
set(figHandle.H_plot,'LineWidth',GenerealLineWidth)
set(figHandle.P_plot,'LineWidth',GenerealLineWidth)
saveas(figHandle.fig,"Figures/FRF_System_Identification",'png')

figHandle = myCoherence(f1,Coh1,"FRF Non-collocated system identification");
set(figHandle.C_plot(1),'LineWidth',GenerealLineWidth)
set(figHandle.C_plot(2),'LineWidth',GenerealLineWidth)
legend(figHandle.Coh_tile,["ps", "s"],'Interpreter','latex','FontSize',LegendFontSize)
saveas(figHandle.fig,"Figures/FRF_System_Identification_Coherence",'png')
function [nfft, noverlap, window] = setFres(Fres, fs)
    nfft = floor(fs/Fres);
    noverlap = floor(nfft/2);
    window = hann(nfft);
end
%% FFW tuning low bandwidth stabilizing controller (lead/lag -lowpass), challenging trajectory
Data_shapeit_ffw_c = load('Controllers_rapport\FFW\Controller_FFW_LL_LPF');
Data_shapeit_ffw_c = Data_shapeit_ffw_c.shapeit_data;

f = Data_shapeit_ffw_c.w/(2*pi);
H = Data_shapeit_ffw_c.P.frf;
figHandle = mybode(f,H,[],"Plant and open loop Stabilizing controller");
set(figHandle.H_plot,'LineWidth',GenerealLineWidth);
set(figHandle.P_plot,'LineWidth',GenerealLineWidth);
C = Data_shapeit_ffw_c.C.frf;
L = C.*H;
figHandle = mybode(f,L,[],[],figHandle);
set(figHandle.H_plot,'LineWidth',GenerealLineWidth);
set(figHandle.P_plot,'LineWidth',GenerealLineWidth);
saveas(figHandle.fig,"Figures/FRF_stabilizingController",'png');

S = 1./(1+L);
figHandle = mybode(f,S,[],"Sensitivity");
set(figHandle.H_plot,'LineWidth',GenerealLineWidth);
set(figHandle.P_plot,'LineWidth',GenerealLineWidth);

%% Store trajectory data (simulation)
%===== Motion profile =====%
FFW_setpoint = load("Setpoints/PlottingData/FFW_setpoint");
accel = FFW_setpoint.setpointData.a;
vel = FFW_setpoint.setpointData.v;
pos = FFW_setpoint.setpointData.s;
t = FFW_setpoint.setpointData.t;

fig_setpoint_FFW = figure;
hold on; grid on;
plot(t,accel,'Color','r','LineWidth',GenerealLineWidth);
plot(t,vel,'Color','b','LineWidth',GenerealLineWidth);
plot(t,pos,'Color','k','LineWidth',GenerealLineWidth);
xlabel('Time [s]','Interpreter','latex','FontSize',AxisFontSize)
legend(["Acceleration $[rad/s^2]$", "Velocity $[rad/s]$", "Position $[rad]$"],'Interpreter','latex', ...
    'Location','southeastoutside','FontSize',LegendFontSize);
title("FFW trajectory","FontSize",TitleFontSize);
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
plot(t,Data_.signals.e(start_-Offset:start_+PlotLength-Offset),'LineWidth',GenerealLineWidth);
plot(t,Data_fc.signals.e(start_fc-Offset:start_fc+PlotLength-Offset),'LineWidth',GenerealLineWidth);
plot(t,Data_fv.signals.e(start_fv-Offset:start_fv+PlotLength-Offset),'LineWidth',GenerealLineWidth);
StaticOffset = 0;%Data_fa.signals.e(start_fa-Offset);
plot(t,Data_fa.signals.e(start_fa-Offset:start_fa+PlotLength-Offset)-StaticOffset,'LineWidth',GenerealLineWidth);
yline(1.1,'LineStyle','--','LineWidth',GenerealLineWidth);
yline(-1.1,'LineStyle','--','LineWidth',GenerealLineWidth);
legend(["No FFW", "K_f_c" , "K_f_v" ,"K_f_a"],'Location','southeast','FontSize',LegendFontSize);
xlabel('$Time [s]$','Interpreter','latex','FontSize',AxisFontSize);
ylabel('$\theta [rad]$','Interpreter','latex','FontSize',AxisFontSize);
title('Feed forward tuning - error profile','FontSize',40);

saveas(fig_ffw,"Figures/FFW_tuning",'png');
fig_ffw_error = figure;
plot(t,Data_fa.signals.e(start_fa-Offset:start_fa+PlotLength-Offset).*1000,'LineWidth',GenerealLineWidth);
hold on;
StaticOffset = Data_fa.signals.e(start_fa-Offset);
e_noOffset = Data_fa.signals.e(start_fa-Offset:start_fa+PlotLength-Offset)-StaticOffset;
plot(t,e_noOffset.*1000,'LineWidth',GenerealLineWidth); %remove static offset
e_max_noOffset = max(abs(e_noOffset));
e_max = max(abs(Data_fa.signals.e(start_fa-Offset:start_fa+PlotLength-Offset)));

grid on;
xlabel('$Time [s]$','Interpreter','latex','FontSize',AxisFontSize)
ylabel('$\theta [mrad]$','Interpreter','latex','FontSize',AxisFontSize)
title('Feed forward tuning - final error','FontSize',TitleFontSize)
legend(["Static offset, e_{max} = " + round(e_max*10^3,2) + " [mrad]", ...
    "No static offset, e_{max} = " + round(e_max_noOffset*10^3,2) + " [mrad]"], ...
    'Location','southeast','FontSize',LegendFontSize)

saveas(fig_ffw_error,"Figures/FFW_final_error",'png');


%% Performance - Region 1
%===== Motion profile 11s =====%
Performance_setpoint_11s = load("Setpoints/PlottingData/Performance_setpoint_11s");
accel = Performance_setpoint_11s.setpointData.a;
vel = Performance_setpoint_11s.setpointData.v;
pos = Performance_setpoint_11s.setpointData.s;
t = Performance_setpoint_11s.setpointData.t;

fig_setpoint_performance = figure;
hold on; grid on;
plot(t,accel,'Color','r','LineWidth',GenerealLineWidth);
plot(t,vel,'Color','b','LineWidth',GenerealLineWidth);
plot(t,pos,'Color','k','LineWidth',GenerealLineWidth);
xlabel('Time [s]','Interpreter','latex','FontSize', AxisFontSize)
legend(["Acceleration $[rad/s^2]$", "Velocity $[rad/s]$", "Position $[rad]$"],'Interpreter','latex', ...
    'Location','southeastoutside','FontSize',LegendFontSize)
title("Trajectory 11 sec",'FontSize',TitleFontSize)
saveas(fig_setpoint_performance,"Figures/Performance_setpoint_11s",'png');

%% ===== error 11s =====%

%Region 1 candidates:
% ProtoLab_setup_45_2410: 6, 9, 10, 12 (double ll, don't use)
% ProtoLab_setup_45_2410_CV2: 2, 4, 5, 6, 7 (find the correct one for
% Controller_13Hz_LL_N53p3_LPF100 -> waarschijnlijk 5, geen peak in PSD at 53 Hz)
%Region 2 candidates:
% ProtoLab_setup_45_2410_CV2: 6 (geen statische offset -> integrator, lijkt
% op de doorontwikkelde controller, controller zit alleen niet in het simulink model??)
Path = "PerformanceMeasurements/ProtoLab_setup_45_2410_CV2/fs_4000_hz/PerformanceData/MeasurementOrder";
Data_perf_11_region1_1 = GetMyData(4,Path); Data_perf_11_region1_1 = Data_perf_11_region1_1.Data;
Data_perf_11_region1_2 =  GetMyData(5,Path); Data_perf_11_region1_2 = Data_perf_11_region1_2.Data;

figure; plot(Data_perf_11_region1_1.signals.e)
hold on;
plot(Data_perf_11_region1_2.signals.e)
legend('data 4', 'data 5')
e = Data_perf_11_region1_1.signals.e;
e_max1 = max(abs(e))
e_rms1 = sqrt(mean(e.^2))

e = Data_perf_11_region1_2.signals.e;
e_max2 = max(abs(e))
e_rms2 = sqrt(mean(e.^2))


%% ===== Correct alingment Region1_1 (data 4) =====%
a = Data_perf_11_region1_1.signals.a;
e = Data_perf_11_region1_1.signals.e;

fs = 4000;
PlotTime = 13;
offsetTime = floor((PlotTime - 11)/2);
PlotLength = PlotTime*fs-1;
offset = offsetTime*fs-1;

figure; plot(sign(a)*max(abs(e))); title("Match samples"); %use to match samples
hold on;
plot(e); title("Match samples"); %use to match samples
for i = 1 : 2
    start = nthStateSwitch(sign(a),2);
    
    n_start = start-offset;
    n_end = start+PlotLength-offset;
    len = n_end-n_start;
    % figure; plot(sign(a(n_start:n_end))) %use to match samples
    % figure; plot(flip(sign(a(n_start:n_end)))) %use to match samples
    endSamples = nthStateSwitch(flip(sign(a(n_start:n_end))),1); %find reversed
    offset = floor((endSamples+offset)/2)
end
start_11 = start-offset;
end_11 = start+PlotLength-offset;

e_max1 = max(abs(e(start_11:end_11)));
e_rms1 = sqrt(mean(e(start_11:end_11).^2));


len = end_11-start_11;
figure; plot(sign(a(start_11:end_11))); title("Fitted data")
hold on;
plot(e(start_11:end_11)/e_max)

e1 = e(start_11:end_11);

%% ===== Correct alingment Region1_2 (data 5) =====%
a = Data_perf_11_region1_2.signals.a;
e = Data_perf_11_region1_2.signals.e;

fs = 4000;
PlotTime = 13;
offsetTime = floor((PlotTime - 11)/2);
PlotLength = PlotTime*fs-1;
offset = offsetTime*fs-1;

figure; plot(sign(a)*max(abs(e))); title("Match samples"); %use to match samples
hold on;
plot(e); title("Match samples"); %use to match samples
for i = 1 : 2
    start = nthStateSwitch(sign(a),6);
    
    n_start = start-offset;
    n_end = start+PlotLength-offset;
    len = n_end-n_start;
    % figure; plot(sign(a(n_start:n_end))) %use to match samples
    % figure; plot(flip(sign(a(n_start:n_end)))) %use to match samples
    endSamples = nthStateSwitch(flip(sign(a(n_start:n_end))),1); %find reversed
    offset = floor((endSamples+offset)/2)
end
start_11 = start-offset;
end_11 = start+PlotLength-offset;

e_max2 = max(abs(e(start_11:end_11)));
e_rms2 = sqrt(mean(e(start_11:end_11).^2))
e_rmsTest = rms(e(start_11:end_11))

len = end_11-start_11;
figure; plot(sign(a(start_11:end_11))); title("Fitted data")
hold on;
plot(e(start_11:end_11)/e_max)

e2 = e(start_11:end_11);

%% Plot Data Region1 1&2 together


t = (-(offset+1)*1/fs:1/fs:(PlotLength-offset-1)*1/fs);
fig_perf_11 = figure;
hold on; grid on;

e_max = max(e_max1,e_max2)

ylim([-(e_max*1000+1) (e_max*1000+1)])
accel_window = (1-abs(sign(a(start_11:end_11)))).*e_max*2;
% plot(t,vel_window.*1000,'LineWidth',2,'Color','r');
area(t,accel_window*1000 ,'FaceColor',"y",'FaceAlpha',0.4,'EdgeColor','none')
area(t,-accel_window*1000 ,'FaceColor',"y",'FaceAlpha',0.4,'EdgeColor','none')
plot(t,e1.*1000,'Color','r','LineWidth',GenerealLineWidth);
plot(t,e2.*1000,'Color','k','LineWidth',GenerealLineWidth);
title("Error C1 vs C2",'FontSize',TitleFontSize)
ylabel('Error [mrad]','Interpreter','latex','FontSize',AxisFontSize);
xlabel('Time [s]','Interpreter','latex','FontSize',AxisFontSize);
ax = gca;
ax.XTick = min(ax.XLim):1:max(ax.XLim);
legend("","Constant Velocity phase","Error C1", "Error C2",'FontSize',LegendFontSize)
ax = gca;
msg = {
    "e_1_{max} = " + round(e_max1 * 1000,2) + " [mrad]"
    "e_1_{rms} = " + round(e_rms1 * 1000,2) + " [mrad]"
    ""
    "e_2_{max} = " + round(e_max2 * 1000,2) + " [mrad]"
    "e_2_{rms} = " + round(e_rms2 * 1000,2) + " [mrad]"
};
text(ax, 0.9, 0.6, msg, ...
    ...
    'Units','normalized', ...
    'HorizontalAlignment','left', ...
    'VerticalAlignment','middle', ...
    'FontSize', LegendFontSize);

saveas(fig_perf_11,"Figures/Performance_Error_11s",'png')
%% PSD 11s -> compare 4 and 5
Fres = 0.1;
nfft = fs/Fres;
window = hanning(nfft);
noverlap = floor(nfft/2);

[PSD1, f] = pwelch(Data_perf_11_region1_1.signals.e,window,noverlap,nfft,fs,"onesided"); %PSD


fig_PSD_11s = figure; 
plot(f,PSD1,'Color','r','LineWidth',1);
yscale log;
xscale log;
grid on;
xlabel('Freq [Hz]');
ylabel('rad^2/Hz');
title("PSD of the error (measurement time: " + Data_perf_11_region1_1.settings.runtime + " seconds)");

hold on;
%figure; 
[PSD2, f] = pwelch(Data_perf_11_region1_2.signals.e,window,noverlap,nfft,fs,"onesided"); %PSD
plot(f,PSD2,'Color','k','LineWidth',1)
yscale log;
xscale log;
grid on;
xlabel('Freq [Hz]');
ylabel('rad^2/Hz');
title("PSD of the error (measurement time: " + Data_perf_11_region1_2.settings.runtime + " seconds)");
saveas(fig_PSD_11s,"Figures/Performance_PSD_11s",'png');
%% Sensitivities V1
clear D;
D(1) = load("Controllers_rapport\Nagemaakt_uit_herinnering\N52p9_LL_LL.mat");
D(2) = load("Controllers_rapport\Nagemaakt_uit_herinnering\N52p9_LL_LL_LPF.mat");
D(3) = load("Controllers_rapport\Nagemaakt_uit_herinnering\N52p9_LL_LL_LPF_I.mat");
D(4) = load("Controllers_rapport\Nagemaakt_uit_herinnering\N52p9_LL_LL_LPF_I_N3p7.mat");


S_fig = figure;
for i = 1:length(D)
    f = D(i).shapeit_data.w./(2*pi);
    H = D(i).shapeit_data.P.frf;
    C = D(i).shapeit_data.C.frf;
    L = C.*H;
    S = 1./(1+L);
    plot(f, 20*log10(abs(S)),'LineWidth',GeneralLineWidth);
    hold on;
end
yline(6,'--','LineWidth',2,'Color','r'); %6db line
legend([ ...
    "It 1", ...
    "It 2", ...
    "It 3", ...
    "It 4", ...
    "6 dB line"...
    ],'Location','southeast','FontSize',24)
grid on;
xscale log;
xlim([0.5 2000])
ylabel('|S| [dB]','FontSize',24);
xlabel('freq [Hz]','FontSize',24);
title('Sensitivity controllers V1');
saveas(S_fig,"Figures\Sens_C_V1",'png');
%% Sensitivities V2
clear D;
D(1) = load("Controllers_rapport\Controllers_V2\N53p3_LL_LPF.mat");
D(2) = load("Controllers_rapport\Controllers_V2\N53p3_LL_LPF_N3p7_I.mat");


S_fig = figure;
for i = 1:length(D)
    f = D(i).shapeit_data.w./(2*pi);
    H = D(i).shapeit_data.P.frf;
    C = D(i).shapeit_data.C.frf;
    L = C.*H;
    S = 1./(1+L);
    plot(f, 20*log10(abs(S)),'LineWidth',GeneralLineWidth);
    hold on;
end
yline(6,'--','LineWidth',2,'Color','r'); %6db line
legend([ ...
    "It 1", ...
    "It 2", ...
    "6 dB line"...
    ],'Location','southeast','FontSize',24)
grid on;
xscale log;
xlim([0.5 2000])
ylabel('|S| [dB]','FontSize',24);
xlabel('freq [Hz]','FontSize',24);
title('Sensitivity controllers V2');
saveas(S_fig,"Figures\Sens_C_V2",'png');
%% PSD comparison V1 11s
clear performanceData;
Fres = 0.1;
performanceData(1) = load("PerformanceReport_traceback\1_Setpoint_11s_13p5Hz_T120_S480000_Iteration_1");
performanceData(2) = load("PerformanceReport_traceback\2_Setpoint_11s_13p5Hz_T120_S480000_Iteration_2");
performanceData(3) = load("PerformanceReport_traceback\3_Setpoint_11s_13p5Hz_T30_S120000_iteration_3.mat");
%performanceData(4) = load("PerformanceReport_traceback\5_Setpoint_10s_13p5Hz_T30_S120000_iteration_3.mat");
%performanceData(5) = load("PerformanceReport_traceback\7_Setpoint_09s_13p5Hz_T30_S120000_Iteration_3.mat");
%performanceData(6) = load("PerformanceReport_traceback\8_Setpoint_09sV2_13Hz_T30_S120000_Iteration_4.mat");

nRuns = numel(performanceData);
CumError = cell(nRuns,1);

Iterations = [
    "It 1 11s", ...
    "It 2 11s", ...
    "It 3 11s", ...
];

PSD_fig = figure;
for i = 1: length(performanceData)
    e = performanceData(i).Data.signals.e;
    a = performanceData(i).Data.signals.a;
    y = performanceData(i).Data.signals.y;
    e_max = max(abs(e(10:end)));
    e_rms = rms(e(10:end));
    fs = performanceData(i).Data.settings.fs;

    nfft = fs/Fres;
    window = hanning(nfft);
    noverlap = floor(nfft/2);
    [PSD, f] = pwelch(e,window,noverlap,nfft,fs,"onesided"); %PSD
    plot(f,PSD,'LineWidth',GeneralLineWidth);
    hold on;
    yscale log;
    xscale log;
    grid on;


    CumError{i} = cumtrapz(f, PSD);  % cumulative integration over f
end
xlabel('freq [Hz]','FontSize',24)
ylabel('power [rad^2/Hz]','FontSize',24)
title('PSD error V1 11s','FontSize',24)
legend(Iterations)
saveas(PSD_fig,"Figures/PSD_V1_11s",'png')

CumError_fig = figure;
for i = 1:nRuns
    plot(f, CumError{i},'LineWidth',GeneralLineWidth); hold on;
end
hold on;
xscale log;
grid on;
xlabel('Frequency [Hz]','FontSize',24);
ylabel('Cumulative error power fraction','FontSize',24);
title('Cumulative error contribution vs frequency','FontSize',24);
legend(Iterations)
saveas(CumError_fig,"Figures/CumError_V1_11s",'png')

%% PSD comparison V1 Region 2
clear performanceData;
Fres = 0.1;
performanceData(1) = load("PerformanceReport_traceback\5_Setpoint_10s_13p5Hz_T30_S120000_iteration_3.mat");
performanceData(2) = load("PerformanceReport_traceback\7_Setpoint_09s_13p5Hz_T30_S120000_Iteration_3.mat");
performanceData(3) = load("PerformanceReport_traceback\8_Setpoint_09sV2_13Hz_T30_S120000_Iteration_4.mat");

nRuns = numel(performanceData);
CumError = cell(nRuns,1);

Iterations = [ ...
    "It 3 10s", ...
    "It 3 09s", ...
    "It 4 09s"...
    ];
PSD_fig = figure;
for i = 1: length(performanceData)
    e = performanceData(i).Data.signals.e;
    a = performanceData(i).Data.signals.a;
    y = performanceData(i).Data.signals.y;
    e_max = max(abs(e(10:end)));
    e_rms = rms(e(10:end));
    fs = performanceData(i).Data.settings.fs;

    nfft = fs/Fres;
    window = hanning(nfft);
    noverlap = floor(nfft/2);
    [PSD, f] = pwelch(e,window,noverlap,nfft,fs,"onesided"); %PSD
    plot(f,PSD,'LineWidth',GeneralLineWidth);
    hold on;
    yscale log;
    xscale log;
    grid on;

    CumError{i} = cumtrapz(f, PSD);  % cumulative integration over f
end
xlabel('freq [Hz]','FontSize',24)
ylabel('power [rad^2/Hz]','FontSize',24)
title('PSD error V1 Region 2','FontSize',24)
legend(Iterations)
saveas(PSD_fig,"Figures/PSD_V1_Region_2",'png')

CumError_fig = figure;
for i = 1:nRuns
    plot(f, CumError{i},'LineWidth',GeneralLineWidth); hold on;
end
hold on;
xscale log;
grid on;
xlabel('Frequency [Hz]','FontSize',24);
ylabel('Cumulative error power fraction','FontSize',24);
title('Cumulative error contribution vs frequency','FontSize',24);
legend(Iterations)
saveas(CumError_fig,"Figures/CumError_V1_Region_2",'png')

%% PSD comparison V2
clear performanceData;
Fres = 0.1;
performanceData(1) = load("PerformanceReport_traceback_V2\5_Setpoint_11s_13p5Hz_T30_S120000_Iteration_1.mat");
performanceData(2) = load("PerformanceReport_traceback_V2\6_Setpoint_11s_13p5Hz_T30_S120000_Iteration_2.mat");

nRuns = numel(performanceData);
CumError = cell(nRuns,1);

Iterations = [ ...
    "It 1 11s", ...
    "It 2 11s", ...
    ];

PSD_fig = figure;
for i = 1: length(performanceData)
    e = performanceData(i).Data.signals.e;
    a = performanceData(i).Data.signals.a;
    y = performanceData(i).Data.signals.y;
    e_max = max(abs(e(10:end)));
    e_rms = rms(e(10:end));
    fs = performanceData(i).Data.settings.fs;

    nfft = fs/Fres;
    window = hanning(nfft);
    noverlap = floor(nfft/2);
    [PSD, f] = pwelch(e,window,noverlap,nfft,fs,"onesided"); %PSD
    plot(f,PSD,'LineWidth',GeneralLineWidth);
    hold on;
    yscale log;
    xscale log;
    grid on;

    CumError{i} = cumtrapz(f, PSD);  % cumulative integration over f
end
xlabel('freq [Hz]','FontSize',24)
ylabel('power [rad^2/Hz]','FontSize',24)
title('PSD error V2','FontSize',24)
legend(Iterations)
saveas(PSD_fig,"Figures/PSD_V2",'png')

CumError_fig = figure;
for i = 1:nRuns
    plot(f, CumError{i},'LineWidth',GeneralLineWidth); hold on;
end
hold on;
xscale log;
grid on;
xlabel('Frequency [Hz]','FontSize',24);
ylabel('Cumulative error power fraction','FontSize',24);
title('Cumulative error contribution vs frequency','FontSize',24);
legend(Iterations)
saveas(CumError_fig,"Figures/CumError_V2",'png')
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


