I = imread('kodim02.png'); % загрузка изображения
figure('Name','Original');
imshow(I); % вывод изображения
sizeI = size(I);

cx = 1; % коэффициент масштабирования по горизонтали
cy = 1; % коэффициент масштабирования по вертикали
teta = 20; % угол поворота
tx = -sizeI(1)/2; % размер сдвига по горизонтали
ty = -sizeI(2)/2; % размер сдвига по вертикали
sv = 0; % коэффициент вертикального скоса
sh = 0; % коэффициент горизонтального скоса

Ip = preobr(I, cx, cy, teta, tx, ty, sv, sh);
% Ip = preobr(Ip, cx, cy, teta, -tx, -ty, sv, sh);
figure('Name','Preobr');
imshow(Ip); % вывод изображения

%% Выполнение интерполяции

Iint = zeros(sizeI .* [2 1 1], 'uint8'); % интерполированная матрица изображения
Iint(1:2:end, :, :) = I; % увеличение картинки в 2 раза путём добавления пустых строк
sizeIint = size(Iint);
Iint = im2double(Iint);

for y = 2:2:sizeIint(1)
    for x = 1:sizeIint(2)
       x1 = x - 1;
       x2 = x + 1;
       y1 = y - 1;
       y2 = y + 1;
       if x1>0 && x1<=sizeIint(2) && x2>0 && x2<=sizeIint(2) && y1>0 && y1<=sizeIint(1) && y2>0 && y2<=sizeIint(1)
            A = (1/((x2 - x1) * (y2 - y1))) * [x2*y2, -x2*y1, -x1*y2, x1*y1; -y2, y1, y2, -y1; -x2, x2, x1, -x1; 1, -1, -1, 1] * [Iint(y1, x1, 1); Iint(y2, x1, 1); Iint(y1, x2, 1); Iint(y2, x2, 1)];
            Iint(y, x, 1) = A(1) + A(2)*x + A(3)*y + A(4)*x*y;
            
            A = (1/((x2 - x1) * (y2 - y1))) * [x2*y2, -x2*y1, -x1*y2, x1*y1; -y2, y1, y2, -y1; -x2, x2, x1, -x1; 1, -1, -1, 1] * [Iint(y1, x1, 2); Iint(y2, x1, 2); Iint(y1, x2, 2); Iint(y2, x2, 2)];
            Iint(y, x, 2) = A(1) + A(2)*x + A(3)*y + A(4)*x*y;
            
            A = (1/((x2 - x1) * (y2 - y1))) * [x2*y2, -x2*y1, -x1*y2, x1*y1; -y2, y1, y2, -y1; -x2, x2, x1, -x1; 1, -1, -1, 1] * [Iint(y1, x1, 3); Iint(y2, x1, 3); Iint(y1, x2, 3); Iint(y2, x2, 3)];
            Iint(y, x, 3) = A(1) + A(2)*x + A(3)*y + A(4)*x*y;
       end
    end
end

Iint = im2uint8(Iint);


A = [];
Iint1 = zeros(sizeI .* [2 2 1], 'uint8'); % интерполированная матрица изображения
Iint1(:, 1:2:end, :) = Iint; % увеличение картинки в 2 раза путём добавления пустых столбцов
sizeIint = size(Iint1);
Iint1 = im2double(Iint1);

for y = 1:sizeIint(1)
    for x = 2:2:sizeIint(2)
       x1 = x - 1;
       x2 = x + 1;
       y1 = y - 1;
       y2 = y + 1;
       if x1>0 && x1<=sizeIint(2) && x2>0 && x2<=sizeIint(2) && y1>0 && y1<=sizeIint(1) && y2>0 && y2<=sizeIint(1)
            A = (1/((x2 - x1) * (y2 - y1))) * [x2*y2, -x2*y1, -x1*y2, x1*y1; -y2, y1, y2, -y1; -x2, x2, x1, -x1; 1, -1, -1, 1] * [Iint1(y1, x1, 1); Iint1(y2, x1, 1); Iint1(y1, x2, 1); Iint1(y2, x2, 1)];
            Iint1(y, x, 1) = A(1) + A(2)*x + A(3)*y + A(4)*x*y;
            
            A = (1/((x2 - x1) * (y2 - y1))) * [x2*y2, -x2*y1, -x1*y2, x1*y1; -y2, y1, y2, -y1; -x2, x2, x1, -x1; 1, -1, -1, 1] * [Iint1(y1, x1, 2); Iint1(y2, x1, 2); Iint1(y1, x2, 2); Iint1(y2, x2, 2)];
            Iint1(y, x, 2) = A(1) + A(2)*x + A(3)*y + A(4)*x*y;
            
            A = (1/((x2 - x1) * (y2 - y1))) * [x2*y2, -x2*y1, -x1*y2, x1*y1; -y2, y1, y2, -y1; -x2, x2, x1, -x1; 1, -1, -1, 1] * [Iint1(y1, x1, 3); Iint1(y2, x1, 3); Iint1(y1, x2, 3); Iint1(y2, x2, 3)];
            Iint1(y, x, 3) = A(1) + A(2)*x + A(3)*y + A(4)*x*y;
       end
    end
end

Iint1 = im2uint8(Iint1);
figure('Name','Interp');
imshow(Iint1); % вывод изображения
