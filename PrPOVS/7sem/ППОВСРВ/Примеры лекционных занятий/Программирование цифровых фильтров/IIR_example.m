%examples for filters

clear;

%highpass IIR filter var7
Wp = [0.5]; %passband
Ws = [0.3]; %stopband
Rp = 0.1;    %passband ripple
Rs = 60;    %stopband attenuation
ftype = 'high';

%bandpass IIR filter var8
% Wp = [0.4 0.6]; %passband
% Ws = [0.2 0.8]; %stopband
% Rp = 0.1;    %passband ripple
% Rs = 45;    %stopband attenuation
% ftype = 'bandpass';
 
% %bandstop IIR filter var9
% Wp = [0.4 0.6]; %passband
% Ws = [0.2 0.8]; %stopband
% Rp = 0.1;    %passband ripple
% Rs = 45;    %stopband attenuation
% ftype = 'stop';

% %lowpass IIR filter var10
% Wp = [0.55]; %passband
% Ws = [0.45]; %stopband
% Rp = 0.1;    %passband ripple
% Rs = 40;    %stopband attenuation
% ftype = 'low';

%passband IIR filter var8
[n, Wpp] = ellipord(Wp, Ws, Rp, Rs);    % determine the minimum order of the filter
[b, a] = ellip(n, Rp, Rs, Wpp, ftype);  % calculate elliptic filter
[sos, g] = tf2sos(b, a);                % determine 2nd order sections

%%% shape of the 'sos' matrix can be interpreted as follows %%%

% | b01 b11 b21 1 a11 a21 | %
% | b02 b12 b22 1 a12 a22 | %
% | ... ... ...   ... ... | %
% | b0L b1L b2L 1 a1L a2L | %

% where 'L' - sections number;
% 'g' output - gain factor.

%%% for more description see MATLAB Documentation %%%

%%% quantization example %%%

bits = 4;
bq = round( b .* ( 2 ^ bits ) ) / ( 2 ^ bits );
aq = round( a .* ( 2 ^ bits ) ) / ( 2 ^ bits );

%%% quantization example %%%



%%% results visualization %%%

freqz(b,a);
figure
freqz(bq,aq)

% figure
% zplane(b, a)
% figure
% zplane(bq, aq)

% figure
% stem(a)
% hold on
% stem(aq, '*m')
% 
% figure
% stem(b)
% hold on
% stem(bq, '*m')
% 
% figure
% impz(b,a)   % impulse response
% 
% figure
% impz(bq,aq)

% fvtool(sos) % filter visualization tools