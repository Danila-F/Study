%filtering demonstration

signalToFilter = [sinGeneratorFunction(60, 256) sinGeneratorFunction(65, 256) sinGeneratorFunction(70, 256)];

exampleFilter = designfilt('lowpassfir', 'FilterOrder', 30, 'PassbandFrequency', 0.45, 'StopBandFrequency', 0.55);

y = filter(exampleFilter.Coefficients, 1, signalToFilter);

plot(y)