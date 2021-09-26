clear;
close all;

fs = 8000;
time = 0.1;
freq1 = 300;
freq2 = 1000;
sigLength = 512;

sinSignal1 = sin(2*pi*freq1*(0:1/fs:time));
sinSignal2 = sin(2*pi*freq2*(0:1/fs:time));

sinSignal1 = sinSignal1(1:sigLength)';
sinSignal2 = sinSignal2(1:sigLength)';
pairSignal = sinSignal1 + 1i.*sinSignal2;

FFTsinSignal1 = fft(sinSignal1);
FFTsinSignal2 = fft(sinSignal2);
FFTpairSignal = fft(pairSignal);

figure
subplot(3, 1, 1)
stem(abs(FFTsinSignal1))
title('Magnitude: signal1')
xlim([0 sigLength]);
subplot(3, 1, 2)
stem(abs(FFTsinSignal2))
title('Magnitude: signal2')
xlim([0 sigLength]);
subplot(3, 1, 3)
stem(abs(FFTpairSignal))
title('Magnitude: signal pair')
xlim([0 sigLength]);

figure
subplot(3, 2, 1)
stem(real(FFTsinSignal1))
title('Real part: signal1')
xlim([0 sigLength]);
subplot(3, 2, 3)
stem(real(FFTsinSignal2))
title('Real part: signal2')
xlim([0 sigLength]);
subplot(3, 2, 5)
stem(real(FFTpairSignal))
title('Real part: signal pair')
xlim([0 sigLength]);

subplot(3, 2, 2)
stem(imag(FFTsinSignal1))
title('Imag part: signal1')
xlim([0 sigLength]);
subplot(3, 2, 4)
stem(imag(FFTsinSignal2))
title('Imag part: signal2')
xlim([0 sigLength]);
subplot(3, 2, 6)
stem(imag(FFTpairSignal))
title('Imag part: signal pair')
xlim([0 sigLength]);

realSinSignal1 = (real(FFTpairSignal(2:sigLength/2)) + real(FFTpairSignal((sigLength:-1:sigLength/2+2))))/2;
realSinSignal1 = [0; realSinSignal1];
imagSinSignal1 = (imag(FFTpairSignal(2:sigLength/2)) - imag(FFTpairSignal(sigLength:-1:sigLength/2+2)))/2;
imagSinSignal1 = [0; imagSinSignal1];

realSinSignal2 = (imag(FFTpairSignal(2:sigLength/2)) + imag(FFTpairSignal((sigLength:-1:sigLength/2+2))))/2;
realSinSignal2 = [0; realSinSignal2];
imagSinSignal2 = (-1.*real(FFTpairSignal(2:sigLength/2)) + real(FFTpairSignal(sigLength:-1:sigLength/2+2)))/2;
imagSinSignal2 = [0; imagSinSignal2];

figure
subplot(2, 2, 1)
stem(real(FFTsinSignal1))
hold on
stem(realSinSignal1, '--*g')
legend('single signal FFT','signal1 from pair FFT', 'Location','south');
title('Real part: signal 1');

subplot(2, 2, 2)
stem(real(FFTsinSignal2))
hold on
stem(realSinSignal2, '--*g')
legend('single signal FFT','signal2 from pair FFT', 'Location','south');
title('Real part: signal 2');

subplot(2, 2, 3)
stem(imag(FFTsinSignal1))
hold on
stem(imagSinSignal1, '--*g')
legend('single signal FFT','signal1 from pair FFT', 'Location','south');
title('Imag part: signal 1');

subplot(2, 2, 4)
stem(imag(FFTsinSignal2))
hold on
stem(imagSinSignal2, '--*g')
legend('single signal FFT','signal2 from pair FFT', 'Location','south');
title('Imag part: signal 2');