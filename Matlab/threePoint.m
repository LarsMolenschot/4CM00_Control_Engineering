function [f, H, S, Coh] = threePoint(d,e,u,window,noverlap,nfft,fs)
Coh = zeros(nfft/2+1,2);
S = zeros(nfft/2+1,2);

%-PS e/d
[PS_est,f_est] = tfestimate(d,-e,window,noverlap,nfft,fs);
[Cps, ~] = mscohere(d,-e,window,noverlap,nfft,fs);
S(:,1) = PS_est;
Coh(:,1) = Cps;

%S u/d
[S_est,~] = tfestimate(d,u,window,noverlap,nfft,fs);
[Cs,~] = mscohere(d,u,window,noverlap,nfft,fs);
S(:,2) = S_est;
Coh(:,2) = Cs;

H_est = PS_est./S_est;
H = H_est;
f = f_est;
end