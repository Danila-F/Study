I = imread('kodim02.png'); % �������� �����������
figure('Name','Original');
imshow(I); % ����� �����������
sizeI = size(I);

cx = 1; % ����������� ��������������� �� �����������
cy = 1; % ����������� ��������������� �� ���������
teta = 20; % ���� ��������
tx = -sizeI(1)/2; % ������ ������ �� �����������
ty = -sizeI(2)/2; % ������ ������ �� ���������
sv = 0; % ����������� ������������� �����
sh = 0; % ����������� ��������������� �����

Ip = preobr(I, cx, cy, teta, tx, ty, sv, sh);
% Ip = preobr(Ip, cx, cy, teta, -tx, -ty, sv, sh);
figure('Name','Preobr');
imshow(Ip); % ����� �����������

%% ���������� ������������

Iint = zeros(sizeI .* [2 1 1], 'uint8'); % ����������������� ������� �����������
Iint(1:2:end, :, :) = I; % ���������� �������� � 2 ���� ���� ���������� ������ �����
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
Iint1 = zeros(sizeI .* [2 2 1], 'uint8'); % ����������������� ������� �����������
Iint1(:, 1:2:end, :) = Iint; % ���������� �������� � 2 ���� ���� ���������� ������ ��������
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
imshow(Iint1); % ����� �����������
