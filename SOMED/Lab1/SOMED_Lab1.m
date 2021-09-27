I = imread('kodim02.png'); %загрузка изображения
Inf = imfinfo('kodim02.png'); %сохранение информации об изображении в переменную

figure('Name','imshow(I)');
imshow(I); %вывод изображения
figure('Name','imagesc(I)');
imagesc(I); %вывод изображения

Id = im2double(I); %перевод формата данных изображения из uint8 в double

figure('Name','imshow(Id)');
imshow(Id); %вывод изображения
figure('Name','imagesc(Id)');
imagesc(Id); %вывод изображения
imwrite (Id, 'kodim02_double.png'); %запись результата в файл

Ig = rgb2gray(I); %преобразование изображения к оттенкам серого

figure('Name','imshow(Ig)');
imshow(Ig); %вывод изображения
figure('Name','imagesc(Ig)');
imagesc(Ig); %вывод изображения
imwrite (Ig, 'kodim02_gray.png'); %запись результата в файл
