#include "Header.h"

int main(int argc, char* argv[])
{
	string command, path;
	string filepath, choice;
	Mat srcImage, dstImage;

	if (argc == 3) //<Program.exe> <path> <malenh>
	{
		path = argv[1];
		command = argv[2];
		srcImage = imread(path, IMREAD_GRAYSCALE);

		if (command == "-sobel")
		{
			detectBySobel(srcImage, dstImage);
			imwrite("D:\\detectBySobel.jpg", dstImage);
			cout << "Your image is detected by Sobel!" << endl;
		}
		if (command == "-prewitt")
		{

			detectByPrewitt(srcImage, dstImage);
			imwrite("D:\\detectByPrewitt.jpg", dstImage);
			cout << "Your image is detected by Prewitt!" << endl;
		}
		if (command == "-laplace")
		{

			detectByLaplace(srcImage, dstImage);
			imwrite("D:\\detectByLaplace.jpg", dstImage);
			cout << "Your image is detected by Laplace!" << endl;
		}
	}
	else if (argc == 5) //<Program.exe> <path> <malenh> <_lowThreshold> <_highThreshold>
	{
		path = argv[1];
		command = argv[2];
		srcImage = imread(path, IMREAD_GRAYSCALE);

		if (command == "-cany")
		{
			int _lowThreshold = stoi(argv[3]), _highThreshold = stoi(argv[4]);
			detectByCany(srcImage, dstImage, _lowThreshold, _highThreshold);
			imwrite("D:\\detectByCany.jpg", dstImage);
			cout << "Your image is detected by Laplace!" << endl;
		}
	}

	return 0;
}