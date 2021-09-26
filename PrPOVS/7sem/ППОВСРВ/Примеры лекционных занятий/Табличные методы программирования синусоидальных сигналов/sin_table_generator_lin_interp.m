clear;

sin_table_128 = xlsread('sin_tables', 'sin_table_128');
sin_table_64 = xlsread('sin_tables', 'sin_table_64');

fs = 8000;

N = 128;
delta = 1.5;
n = 1:N;

frequency = delta /((1/fs)*N);
signalFracPoints = delta * n;

intPart = fix(signalFracPoints);
fracPart = mod(signalFracPoints, intPart);

indexes = mod(intPart, N) + 1;
nextIndexes = mod((indexes+1), N);
nextIndexes(nextIndexes == 0) = 1;

for i = 1:N
    sigFracStep(i) = sin_table_128(indexes(i)) + fracPart(i) * ( sin_table_128(nextIndexes(i)) - sin_table_128(indexes(i)) );
end
sigFracStep = [0 sigFracStep(1:end-1)];    % alignment for matching ML sin
sigFracStep = sigFracStep ./ 2^15;


sigFracStepML = sin( 2*pi*frequency*(0:1/fs:(length(n)-1)/fs) )';   % reference signal generated via MATLAB
sigFracStepML = sigFracStepML(1:length(sigFracStep));
errorPureFracStep = sigFracStepML - sigFracStep';

figure
spectrogram(sigFracStep, 128, 64, 128, fs, 'yaxis');
colorbar('off');
title('Signal generated by the sin table');
figure
spectrogram(sigFracStepML, 128, 64, 128, fs, 'yaxis');
colorbar('off');
title('Signal generated by the built-in function');

figure
plot(sigFracStep);
title('Signal generated by the sin table');
hold on;
plot(sigFracStepML, '--m');
title('Signal generated by the built-in function');
plot(errorPureFracStep, 'r');
xlim([1 length(sigFracStep)]);
ylim([min(sigFracStep) max(sigFracStep)]);
legend('Signal generated by the sin table', 'Signal generated by the built-in function');
hold off;