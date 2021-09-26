function [thd] = TotalHarmonicDistortion(signalUnderTest, fftSize, A)

    testSignalLength = length(signalUnderTest);

    %energy of the whole signal
    overallEnergy = sum( signalUnderTest.^2 ) * (1 / testSignalLength);
    
    signalFreqDomain = zeros(fftSize, 1);
    signalFreqDomainReal = zeros(fftSize, 1);
    signalFreqDomainImag = zeros(fftSize, 1);
    
    %Fourier transform
    for freqBin = 1:fftSize
        for sampleN = 1:testSignalLength            
            %exponential form
            signalFreqDomain(freqBin) = signalFreqDomain(freqBin) + signalUnderTest(sampleN) * exp(-1*1i*(2*pi/testSignalLength)*(sampleN-1)*(freqBin-1) );
            
            %trigonometric form
            signalFreqDomainReal(freqBin) = signalFreqDomainReal(freqBin) + signalUnderTest(sampleN) * cos(2*pi/testSignalLength*(sampleN-1)*(freqBin-1));
            signalFreqDomainImag(freqBin) = signalFreqDomainImag(freqBin) + signalUnderTest(sampleN) * sin(2*pi/testSignalLength*(sampleN-1)*(freqBin-1));
        end
        
        %exponential form normalization
        signalFreqDomain(freqBin) = signalFreqDomain(freqBin)*(1/(testSignalLength));
        
        %trigonometric form normalization
        signalFreqDomainReal(freqBin) = signalFreqDomainReal(freqBin)*(1/(testSignalLength/2));
        signalFreqDomainImag(freqBin) = signalFreqDomainImag(freqBin)*(1/(testSignalLength/2));
    end
    %Fourier transform with help of built-in function (for verification)
    signalFreqDomainML = fft(signalUnderTest, fftSize);
    
    %energy of one harmonic : harmonicNumber+1 since in frequency domain there is zero frequency! 
    fundamentalEnergy =  2 * (abs( signalFreqDomain(A+1) ) )^2 ; 
    
    thd = (overallEnergy - fundamentalEnergy) ./ overallEnergy;
end