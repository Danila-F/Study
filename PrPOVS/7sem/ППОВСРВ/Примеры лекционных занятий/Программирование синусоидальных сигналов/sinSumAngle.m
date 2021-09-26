clear;

harmonicNumber = 2;
harmonicLenght = 176;
a = 2*pi/harmonicLenght;

% ��������� �������� ��� ����������� �������� ������ � �������� k-� ���������
Sk = 0; % �������� ������ ��� �������� ���������
Ck = 1; % �������� �������� ��� �������� ���������
S1 = sin(a);    % �������� ������ ������������ ���������� ("������ �����") ��� ������ ���������
C1 = cos(a);    % �������� �������� ������������ ���������� ("������ �����") ��� ������ ���������
Sk_prev = Sk;
Ck_prev = Ck;
    
%-----����������� ��������� �������� ������ � �������� k-� ���������-----%
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

%-----���� ��������� ��������������� �������-----%
for n = 2:harmonicLenght
    Sn(n) = Ck*Sn(n-1) + Sk*Cn(n-1);
    Cn(n) = Ck*Cn(n-1) - Sk*Sn(n-1);
end

plot(Sn, 'm')
hold on
plot(Cn, '--b')
hold off
legend('�����', '�������');
xlim([0 harmonicLenght])

% nonFractionalNumbers = int16(Sn .* (2^15) );  % ��� �������� ������ ���������� �������� �� 32768 (������ Q15, �.�. 15 �������� �� ������� �����)
% figure;
% plot(nonFractionalNumbers)