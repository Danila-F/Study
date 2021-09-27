function [Ip] = preobr(I, cx, cy, teta, tx, ty, sv, sh)
%PREOBR ����������� ����������� �� �������� ����������
%   ������������ ���������������, �������, �����, ���� �� ����� ����

sizeI = size(I);

Tm = eye(3); % ������� ���������������
Tm(1, 1) = cx;
Tm(2, 2) = cy;

Tp = eye(3); % ������� ��������
Tp(1, 1) = cos(teta*pi/180);
Tp(1, 2) = sin(teta*pi/180);
Tp(2, 1) = -sin(teta*pi/180);
Tp(2, 2) = cos(teta*pi/180);

Ts = eye(3); % ������� ������
Ts(3, 1) = tx;
Ts(3, 2) = ty;

Ts1 = eye(3); % ������� ��������� ������
Ts1(3, 1) = -tx;
Ts1(3, 2) = -ty;

Tv = eye(3); % ������� ������������� �����
Tv(2, 1) = sv;

Tg = eye(3); % ������� ��������������� �����
Tg(1, 2) = sh;

T = Tm * Ts * Tp * Ts1 * Tv * Tg; % ������� ��������� ��������������
Ip = zeros(sizeI, 'uint8'); % ��������������� ������� �����������

for x = 1:sizeI(1)
    for y = 1:sizeI(2)
       p = [x y 1] / T;
       p1 = round(p(1));
       p2 = round(p(2));
       if p1<=sizeI(1) && p2<=sizeI(2) && p1>0 && p2>0
           Ip(x, y, :) = I(p1, p2, :);
       end
    end
end

end
