clear
close all

sin_table_128 = xlsread('sin_tables', 'sin_table_128');
sin_table_64 = xlsread('sin_tables', 'sin_table_64');

fs = 8000;

N = 128;
n = 1:N;

tableStep = 10;
indexTable = mod(tableStep .* n, N) + 1;

sigIntStep = sin_table_128( indexTable )./2^15; % sine table array name needs to be renamed corresponding to the "N"
sigIntStep = [0; sigIntStep(1:end-1)];    % alignment for matching ML sin

freq = tableStep/((1/fs)*N);    % reference sin frequency in Hz
sigIntStepML = sin( 2*pi*freq*(0:1/fs:(length(n)-1)/fs) )';

figure
plot(sigIntStep)
xlim([1 length(sigIntStep)]);
hold on
plot(sigIntStepML, '--m')
plot(sigIntStepML - sigIntStep, 'r')