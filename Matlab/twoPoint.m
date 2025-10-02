function [f, H, S, L, Coh] = twoPoint(d,u,r,c_p,c_i,c_d,window,noverlap,nfft,fs)
%This function takes as input signals d, u and r with C_resp being the
%controller response over the desired frequency range f.

[Sud,f]  = cpsd(u, d, window, noverlap, nfft, fs);
[Sdd,f] = cpsd(d, d, window, noverlap, nfft, fs);

[Crd, ~] = mscohere(r,d,window,noverlap,nfft,fs);
[Cud, ~] = mscohere(u,d,window,noverlap,nfft,fs);
Coh(:,1) = Crd;
Coh(:,2) = Cud;

s = tf('s');
C = tf(c_p*(1+c_d*s+c_i*(1/s)));
C_resp = squeeze(freqresp(C, 2*pi*f)); 

S = (Sud./Sdd);
H = (1./C_resp).*((1./S)-1);
L = (1./(Sud./Sdd))-1;
end