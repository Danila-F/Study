clear;

inputData = [0 4 2 6 1 5 3 7];
outputData = zeros(1, 8);
numberOfDigits = 3;
arrayLength = size(inputData, 2);
divider = 2;
indexBits = dec2bin(0, numberOfDigits);

for elementsCnt = 1:max(size(inputData))
    outputData(elementsCnt) = inputData(bin2dec(indexBits)+1);  %outputData will be in bit-reverse order
    
    for bitCnt = 1:numberOfDigits
        if indexBits(bitCnt) == '0'
            addend = arrayLength/(divider*bitCnt);  %addend will contain brackets with sub: (1-2-4-...-N/4-N/2)
            for i = bitCnt-1:-1:1
                addend = addend - arrayLength/(divider*i);
            end
            
            indexBits = dec2bin(bin2dec(indexBits) + addend, numberOfDigits);
            break;
        end
    end
end
