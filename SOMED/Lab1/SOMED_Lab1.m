I = imread('kodim02.png'); %�������� �����������
Inf = imfinfo('kodim02.png'); %���������� ���������� �� ����������� � ����������

figure('Name','imshow(I)');
imshow(I); %����� �����������
figure('Name','imagesc(I)');
imagesc(I); %����� �����������

Id = im2double(I); %������� ������� ������ ����������� �� uint8 � double

figure('Name','imshow(Id)');
imshow(Id); %����� �����������
figure('Name','imagesc(Id)');
imagesc(Id); %����� �����������
imwrite (Id, 'kodim02_double.png'); %������ ���������� � ����

Ig = rgb2gray(I); %�������������� ����������� � �������� ������

figure('Name','imshow(Ig)');
imshow(Ig); %����� �����������
figure('Name','imagesc(Ig)');
imagesc(Ig); %����� �����������
imwrite (Ig, 'kodim02_gray.png'); %������ ���������� � ����
