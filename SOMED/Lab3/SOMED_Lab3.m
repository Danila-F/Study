% преобразованние исходных изображений к типу double [0 255]
I1 = double(imread('1_1.tif'));
I2 = double(imread('1_2.tif'));
I3 = double(imread('1_3.tif'));
I4 = double(imread('1_4.tif'));

scale = 256;

gist1 = gist(I1);
gist2 = gist(I2);
gist3 = gist(I3);
gist4 = gist(I4);

figure('Name','Before'); % вывод оригиналных изображений и их гистрограмм
subplot(4, 2, 1); imshow(I1, [0 (scale - 1)]);
subplot(4, 2, 2); plot(gist1, 'o');
subplot(4, 2, 3); imshow(I2, [0 (scale - 1)]);
subplot(4, 2, 4); plot(gist2, 'o');
subplot(4, 2, 5); imshow(I3, [0 (scale - 1)]);
subplot(4, 2, 6); plot(gist3, 'o');
subplot(4, 2, 7); imshow(I4, [0 (scale - 1)]);
subplot(4, 2, 8); plot(gist4, 'o');

% эквализация гистрограмм
[T1, Ieq1] = ekval(gist1, I1);
[T2, Ieq2] = ekval(gist2, I2);
[T3, Ieq3] = ekval(gist3, I3);
[T4, Ieq4] = ekval(gist4, I4);

figure('Name','After'); % вывод изображений после эквализации и их гистрограмм
subplot(4, 2, 1); imshow(Ieq1, [0 (scale - 1)]);
subplot(4, 2, 2); plot(gist(Ieq1), 'o');
subplot(4, 2, 3); imshow(Ieq2, [0 (scale - 1)]);
subplot(4, 2, 4); plot(gist(Ieq2), 'o');
subplot(4, 2, 5); imshow(Ieq3, [0 (scale - 1)]);
subplot(4, 2, 6); plot(gist(Ieq3), 'o');
subplot(4, 2, 7); imshow(Ieq4, [0 (scale - 1)]);
subplot(4, 2, 8); plot(gist(Ieq4), 'o');

%%

I2_1 =  wextend('2d', 'zpd', double(imread('2_1.tif')), 2); sizeI2_1 = size(I2_1);
figure('Name','Before');
imshow(I2_1, [0 (scale - 1)]);

% локальная эквализация окрестностью 3x3
Ieq2_1_1 = zeros(sizeI2_1);
for a = 3:(sizeI2_1(1)-2)
   for b = 3:(sizeI2_1(2)-2)
       tempI = I2_1(a-1:a+1, b-1:b+1);
       [~, Ieq2_1_1(a-1:a+1, b-1:b+1)] = ekval(gist(tempI), tempI);
   end
end

% локальная эквализация окрестностью 5x5
Ieq2_1_2 = zeros(sizeI2_1);
for a = 3:(sizeI2_1(1)-2)
   for b = 3:(sizeI2_1(2)-2)
       tempI = I2_1(a-2:a+2, b-2:b+2);
       [T, Ieq2_1_2(a-2:a+2, b-2:b+2)] = ekval(gist(tempI), tempI);
   end
end

figure('Name','After');
subplot(1, 2, 1); imshow(Ieq2_1_1, [0 (scale - 1)]);
subplot(1, 2, 2); imshow(Ieq2_1_2, [0 (scale - 1)]);

%%

m = 15;
I3_1 = wextend('2d', 'zpd', double(imread('3_1.tif')), (m-1)/2);
figure('Name','Before');
imshow(I3_1, [0 (scale - 1)]);

Ifiltr3_1 = my_filt2d(I3_1, my_filt(m, m)); % фильтрация сглаживающим фильтром 15 x 15
figure('Name','After');
subplot(1, 2, 1); imshow(Ifiltr3_1, [0 (scale - 1)]);

for x = 1:size(Ifiltr3_1, 1) % пороговая фильтрация
    for y = 1:size(Ifiltr3_1, 2)
        if Ifiltr3_1(x, y) > 64
           Ifiltr3_1(x, y) = 255;
        else
            Ifiltr3_1(x, y) = 0;
        end
    end
end
subplot(1, 2, 2); imshow(Ifiltr3_1, [0 (scale - 1)]);

%%

m = 3;
step = (m-1)/2;
I4_1 = wextend('2d', 'zpd', double(imread('4_1.tif')), step);
figure('Name','Before');
imshow(I4_1, [0 (scale - 1)]);

Ifiltr4_1 = my_filt2d(I4_1, my_filt(m, m)); % фильтрация сглаживающим фильтром 3 x 3
figure('Name','After');
subplot(1, 2, 1); imshow(Ifiltr4_1, [0 (scale - 1)]);

Temp = zeros(m, m);
Temp_s = zeros(m^2, 1);
for x = (1 + step):(size(Ifiltr4_1, 1) - step) % медианная фильтрация
    for y = (1 + step):(size(Ifiltr4_1, 2) - step)
        Temp = Ifiltr4_1((x - step):(x + step), (y - step):(y + step));
        Temp_s = sort(Temp(:));
        Ifiltr4_1(x, y) = Temp_s((m^2+1)/2);
    end
end
subplot(1, 2, 2); imshow(Ifiltr4_1, [0 (scale - 1)]);

%%

m = 3;
step = (m-1)/2;
I5_1 = wextend('2d', 'zpd', double(imread('5_1.tif')), step);
figure('Name','Before');
imshow(I5_1, [0 (scale - 1)]);

Ifiltr5_1 = laplasian(I5_1); % рассчёт лапласиана 3 x 3 для оригинального изображения
figure('Name','After');
subplot(1, 2, 1); imshow(Ifiltr5_1, [0 (scale - 1)]);

Ifiltr5_1 = I5_1 - Ifiltr5_1; % добавление фона на изображение
subplot(1, 2, 2); imshow(Ifiltr5_1, [0 (scale - 1)]);
