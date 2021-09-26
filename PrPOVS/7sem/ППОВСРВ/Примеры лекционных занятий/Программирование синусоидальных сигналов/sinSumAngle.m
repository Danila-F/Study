clear;

harmonicNumber = 2;
harmonicLenght = 176;
a = 2*pi/harmonicLenght;

% начальные значения для определения значений синуса и косинуса k-й гармоники
Sk = 0; % значение синуса для нулевого аргумента
Ck = 1; % значение косинуса для нулевого аргумента
S1 = sin(a);    % значение синуса минимального приращения ("вторая точка") для первой гармоники
C1 = cos(a);    % значение косинуса минимального приращения ("вторая точка") для первой гармоники
Sk_prev = Sk;
Ck_prev = Ck;
    
%-----определение начальных значений синуса и косинуса k-й гармоники-----%
for k = 1:harmonicNumber
    Sk = C1*Sk_prev + S1*Ck_prev;
    Ck = C1*Ck_prev - S1*Sk_prev;
    
    Sk_prev = Sk;
    Ck_prev = Ck;
end

Sn = zeros(1, harmonicLenght);
Cn = zeros(1, harmonicLenght);
Sn(1) = 0;
Cn(1) = 1;

%-----цикл генерации синусоидального сигнала-----%
for n = 2:harmonicLenght
    Sn(n) = Ck*Sn(n-1) + Sk*Cn(n-1);
    Cn(n) = Ck*Cn(n-1) - Sk*Sn(n-1);
end

plot(Sn, 'm')
hold on
plot(Cn, '--b')
hold off
legend('синус', 'косинус');
xlim([0 harmonicLenght])

% nonFractionalNumbers = int16(Sn .* (2^15) );  % для перевода дробей необходимо умножить на 32768 (формат Q15, т.е. 15 разрядов на дробную часть)
% figure;
% plot(nonFractionalNumbers)