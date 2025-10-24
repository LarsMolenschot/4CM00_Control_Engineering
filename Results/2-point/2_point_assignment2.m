s = tf('s');

Kp = 2;
Kd = 0.02;

f_filt = 200;
b_filt = 0.7;

C_pd = (Kp + s*Kd);
C_filter = (1)/((1/(2*pi*f_filt)^2)*s^2+((2*b_filt)/(2*pi*f_filt))*s+1);

C_total = C_pd * C_filter;



d = Data.signals.d;
e = Data.signals.e;
y = Data.signals.y;
u = Data.signals.u;
r = Data.signals.r;
Trun = Data.settings.runtime;
Fs = Data.settings.fs;

%C_disc = c2d(C_total, 1/Fs, 'tustin');

frames = 120;

nfft = Trun./frames*Fs;
noverlap = nfft/2;
window = hann(nfft);

[f, H, S, L, Coh, C_resp] = twoPoint(d, u, r, C_total, window, noverlap, nfft, Fs);

[f2, H2, S2, C2] = threePoint(d,e,u,window,noverlap,nfft,Fs);
L2 = H2.*C_resp;

PlotProcessedData([ ...
    struct('f',f,'H',H,'S',S,'C',[]),...
    % struct('f',f2,'H',H2,'S',S2,'C',[]),...
    struct('f',f,'H',L,'S',S,'C',[]),...
    % struct('f',f2,'H',L2,'S',S,'C',[]),...
    ], "Test")

