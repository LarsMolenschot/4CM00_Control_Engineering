function [f, H, S, L, Coh, C_resp] = twoPoint(d,u,r,C_tf,window,noverlap,nfft,fs)
%This function takes as input signals d, u and r with C_resp being the
%controller response over the desired frequency range f.

[Sud,f]  = cpsd(u, d, window, noverlap, nfft, fs);
[Sdd,~] = cpsd(d, d, window, noverlap, nfft, fs);

[Crd, ~] = mscohere(r,d,window,noverlap,nfft,fs);
[Cud, ~] = mscohere(u,d,window,noverlap,nfft,fs);
Coh(:,1) = Crd;
Coh(:,2) = Cud;

C_resp = squeeze(freqresp(C_tf, 2*pi*f)); 

S = (Sud./Sdd);
H = (1./C_resp).*((1./S)-1);
L = (1./S)-1;
end