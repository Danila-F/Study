function [Ifltr] = my_filt2d(I, w)
%MY_FILT2D filtering

sizeI = size(I);
Ifltr = zeros(sizeI);
[m, n] = size(w);
a = (m-1)/2;
b = (n-1)/2;
for x = (1 + a):(sizeI(1) - a)
    for y = (1 + b):(sizeI(2) - b)
        sum = 0;
        
        for s = -a:a
           for t = -b:b
               sum = sum + (w(s+a+1, t+b+1) * I(x - s, y - t));
           end
        end
        
        Ifltr(x, y) = round(sum);
    end
end

end

