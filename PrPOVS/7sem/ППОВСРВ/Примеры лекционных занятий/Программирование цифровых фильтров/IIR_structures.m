clear;

signalToFilter = [sinGeneratorFunction(60, 256) sinGeneratorFunction(65, 256) sinGeneratorFunction(70, 256)];

Wp = [0.5]; %passband
Ws = [0.6]; %stopband
Rp = 0.1;    %passband ripple
Rs = 40;     %stopband attenuation
ftype = 'low';

[filterOrder, Wpp] = ellipord(Wp, Ws, Rp, Rs);    % determine the minimum order of the filter
[b, a] = ellip(filterOrder, Rp, Rs, Wpp, ftype);  % calculate elliptic filter
[sos, g] = tf2sos(b, a);                % determine 2nd order sections


%%% straight form
y = zeros( length(signalToFilter), 1 );    % output signal (filtered)
numerator = zeros( length(signalToFilter), 1 );
denumerator = zeros( length(signalToFilter), 1 );

for n = filterOrder+2:length(signalToFilter) - filterOrder
    for k = 1:filterOrder+1
       numerator(n) = numerator(n) + b(k) * signalToFilter(n - k);
    end
    
    for k = 1:filterOrder
       denumerator(n) = denumerator(n) + a(k+1) * y(n - k);
    end
    
    y(n) = numerator(n) - denumerator(n);
end

y_ML = filter( b, a, signalToFilter );  % filtering with built-in func, for comparison



%%% with 2nd order sections, canonical section
y = zeros( length(signalToFilter), 1 );    % output signal (filtered)
w = zeros( 2 .* length(signalToFilter), 1 );

%%% 1st section
for n = filterOrder+2:length(signalToFilter) - filterOrder
    w(n) = signalToFilter(n) - ( sos(1, 5) * w(n-1) + sos(1, 6) * w(n-2) );
end

for n = filterOrder+2:length(signalToFilter) - filterOrder
    y(n) = sos(1, 1) * w(n) + sos(1, 2) * w(n-1) + sos(1, 3) * w(n-2);
end

%%% 2nd section
for n = filterOrder+2:length(signalToFilter) - filterOrder
    w(n) = y(n) - ( sos(2, 5) * w(n-1) + sos(2, 6) * w(n-2) );
end

for n = filterOrder+2:length(signalToFilter) - filterOrder
    y(n) = sos(2, 1) * w(n) + sos(2, 2) * w(n-1) + sos(2, 3) * w(n-2);
end

%%% 3rd section
for n = filterOrder+2:length(signalToFilter) - filterOrder
    w(n) = y(n) - ( sos(3, 5) * w(n-1) + sos(3, 6) * w(n-2) );
end

for n = filterOrder+2:length(signalToFilter) - filterOrder
    y(n) = sos(3, 1) * w(n) + sos(3, 2) * w(n-1) + sos(3, 3) * w(n-2);
end

y = y .* g; %scaling