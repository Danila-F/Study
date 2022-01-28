function [w] = my_filt(m, n)
%MY_FILT ������������ ������ m x n

a = (m-1)/2;
b = (n-1)/2;
w = zeros(m, n);

for s = -a:a
   for t = -b:b
      w(s+a+1, t+b+1) = 1/(m*n);
   end
end

end
