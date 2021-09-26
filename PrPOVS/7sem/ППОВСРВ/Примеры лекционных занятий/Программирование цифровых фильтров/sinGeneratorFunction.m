function [signal] = sinGeneratorFunction(harmonicNumber, harmonicLenght)

a = 2*pi/harmonicLenght;

s_k = 0;    %шаг приращения аргумента для k-й гармоники
a_n = zeros(1, harmonicLenght);
a_n(1) = 90;   %аргумент (начальное значение)
threshold = 0.03125;    %порог деления аргумента (фактически, точность генератора)

%-----определение значения шага приращения для конкретной гармоники-----%
for i = 1:harmonicNumber
    s_k = s_k + a;
end

%-----определение аргументов для конкретной гармоники-----%
for i = 2:harmonicLenght
    a_n(i) = a_n(i-1) + s_k;
end

%-----основной цикл алгоритма-----%
signal = zeros(1, harmonicLenght);
for i = 1:harmonicLenght
    m = 0;  %данное значение показывает сколько раз нужно делить аргумент, что бы sin(a_n) = a_n  с заданной точностью
    while a_n(i) > threshold
        a_n(i) = a_n(i)/2;
        m = m + 1;
    end

    %цикл генерации синусоидального сигнала
    sin_a = a_n(i);
    cos_a = 1 - (a_n(i)^2)/2;   %значение косинуса используется в формуле sin(2a) = 2sin(a)cos(a)
    for j = 1:m
        sin_a_prev = sin_a;
        sin_a = 2*sin_a*cos_a;
        cos_a = 1 - 2*sin_a_prev^2;
    end
    signal(i) = sin_a;
end

end