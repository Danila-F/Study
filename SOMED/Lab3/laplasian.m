function [Iret] = laplasian(I)
%LAPLASIAN Compiting laplassian 3 x 3

m = 3;
step = (m-1)/2;
Iret = zeros(size(I));
for x = (1 + step):(size(I, 1) - step)
    for y = (1 + step):(size(I, 2) - step)
        Iret(x, y) = I(x+1, y) + I(x-1, y) + I(x, y+1) + I(x, y-1) - 4*I(x, y);
    end
end

end

