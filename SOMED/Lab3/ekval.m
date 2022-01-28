function [T, Ieq] = ekval(gistag, I)
%EKVAL making histogram and image equalization

scale = size(gistag);
T = zeros(scale);
for k = 1:scale(2)
    T(k) = round( (scale(2) - 1) * sum(gistag(1:k)) );
end

sizeI = size(I);
Ieq = zeros(sizeI);
for a = 1:(sizeI(1)*sizeI(2))
    Ieq(a) = T(I(a)+1);
end

end

