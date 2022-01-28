function [gistag] = gist(imag)
%GIST making histogram from image 2-dimention matrix

gistag = zeros(1, 256);
sizeImag = size(imag);
for a = 1:(sizeImag(1)*sizeImag(2))
    gistag(imag(a) + 1) = gistag(imag(a) + 1) + 1;
end
gistag = gistag ./ (sizeImag(1) * sizeImag(2));

end
