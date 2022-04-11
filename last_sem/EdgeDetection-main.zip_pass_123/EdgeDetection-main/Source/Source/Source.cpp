#include "Header.h"

int detectByLaplace(const Mat& sourceImage, Mat& destinationImage)
{
	if (sourceImage.empty())
		return 1;

	Convolution convolution;
	vector<int> kernel;
	Mat laplacian;

	kernel.push_back(1); kernel.push_back(1); kernel.push_back(1);
	kernel.push_back(1); kernel.push_back(-8); kernel.push_back(1);
	kernel.push_back(1); kernel.push_back(1); kernel.push_back(1);

	convolution.SetKernel(kernel, 1.0f, 3, 3);
	convolution.DoConvolution(sourceImage, laplacian);

	destinationImage = Mat(sourceImage.rows, sourceImage.cols, CV_8UC1, Scalar(0));

	int rowStep = sourceImage.cols;

	short* pRowLap = (short*)(laplacian.data) + rowStep;
	uchar* pRowDst = destinationImage.data + rowStep;
	float threshold = 150;

	for (int i = 1; i < sourceImage.rows - 1; i++, pRowLap += rowStep, pRowDst += rowStep)
	{
		short* pDataLap = pRowLap;
		uchar* pDataDst = pRowDst;
		for (int j = 1; j < sourceImage.cols - 1; j++, pDataLap++, pDataDst++)
			if (*pDataLap == 0)
			{
				if (pDataLap[rowStep] * pDataLap[-rowStep] < 0 && abs(pDataLap[rowStep] - pDataLap[-rowStep]) >= threshold)
					*pDataDst = 255;
				if (pDataLap[1] * pDataLap[-1] < 0 && abs(pDataLap[1] - pDataLap[-1]) >= threshold)
					*pDataDst = 255;
				if (pDataLap[rowStep + 1] * pDataLap[-rowStep - 1] < 0 && abs(pDataLap[rowStep + 1] - pDataLap[-rowStep - 1]) >= threshold)
					*pDataDst = 255;
				if (pDataLap[rowStep - 1] * pDataLap[-rowStep + 1] < 0 && abs(pDataLap[rowStep - 1] - pDataLap[-rowStep + 1]) >= threshold)
					*pDataDst = 255;
			}
			else
			{
				if (*pDataLap * pDataLap[rowStep] < 0 && abs(*pDataLap - pDataLap[rowStep]) >= threshold)
					*pDataDst = 255;
				if (*pDataLap * pDataLap[rowStep + 1] < 0 && abs(*pDataLap - pDataLap[rowStep + 1]) >= threshold)
					*pDataDst = 255;
				if (*pDataLap * pDataLap[1] < 0 && abs(*pDataLap - pDataLap[1]) >= threshold)
					*pDataDst = 255;
			}
	}

	return 0;
}

int detectBySobel(const Mat& sourceImage, Mat& destinationImage)
{
	if (sourceImage.empty())
		return 1;

	Convolution convolution;
	vector<int> kernelX;
	vector<int> kernelY;
	float division = 1.0f;
	Mat dx, dy;

	/*
	|1  0  -1|   1
	|2  0  -2| * -  =  Kx
	|1  0  -1|   4
	*/
	kernelX.push_back(1); kernelX.push_back(0); kernelX.push_back(-1);
	kernelX.push_back(2); kernelX.push_back(0); kernelX.push_back(-2);
	kernelX.push_back(1); kernelX.push_back(0); kernelX.push_back(-1);

	/*
	|-1  -2  -1|   1
	| 0   0   0| * -  =  Ky
	| 1   2   1|   4
	*/
	kernelY.push_back(-1); kernelY.push_back(-2); kernelY.push_back(-1);
	kernelY.push_back(0); kernelY.push_back(0); kernelY.push_back(0);
	kernelY.push_back(1); kernelY.push_back(2); kernelY.push_back(1);

	division = 4.0f;

	convolution.SetKernel(kernelX, division, 3, 3);
	convolution.DoConvolution(sourceImage, dx);
	convolution.SetKernel(kernelY, division, 3, 3);
	convolution.DoConvolution(sourceImage, dy);

	destinationImage = Mat(sourceImage.rows, sourceImage.cols, CV_8UC1, Scalar(0));
	int rowStep = sourceImage.cols;

	short* pRowX = (short*)(dx.data);
	short* pRowY = (short*)(dy.data);
	uchar* pRow = destinationImage.data;
	int threshold = 1024;

	// tại dx dy có giá trị âm xuất ra ảnh bị sai nên abs lên để xuất ảnh
	/*Mat X = Mat(dx.rows, dx.cols, CV_8UC1, Scalar(0));
	Mat Y = Mat(dy.rows, dy.cols, CV_8UC1, Scalar(0));
	uchar* pYRow = Y.data;
	uchar* pXRow = X.data;
	for (int i = 0; i < Y.rows; i++, pXRow += rowStep, pYRow += rowStep, pRowY += rowStep, pRowX += rowStep) {
		short* pDataX = pRowX;
		short* pDataY = pRowY;
		uchar* pYData = pYRow;
		uchar* pXData = pXRow;
		for (int j = 0; j < Y.cols; j++, pDataX++, pDataY++, pXData++, pYData++) {
			*pXData = abs(*pDataX);
			*pYData = abs(*pDataY);
		}

	}
	imwrite("D:\\Y.jpg", Y);
	imwrite("D:\\X.jpg", X);*/

	for (int i = 0; i < sourceImage.rows; i++, pRowX += rowStep, pRowY += rowStep, pRow += rowStep)
	{
		short* pDataX = pRowX;
		short* pDataY = pRowY;
		uchar* pData = pRow;
		for (int j = 0; j < sourceImage.cols; j++, pDataX++, pDataY++, pData++)
		{
			if (*pDataX * *pDataX + *pDataY * *pDataY >= threshold)
				*pData = 255;
		}
	}

	return 0;
}

int detectByPrewitt(const Mat& sourceImage, Mat& destinationImage)
{
	if (sourceImage.empty())
		return 1;

	Convolution convolution;
	vector<int> kernelX;
	vector<int> kernelY;
	float division = 1.0f;
	Mat dx, dy;

	/*
	|1  0  -1|   1
	|1  0  -1| * -  =  Kx
	|1  0  -1|   3
	*/
	kernelX.push_back(1); kernelX.push_back(0); kernelX.push_back(-1);
	kernelX.push_back(1); kernelX.push_back(0); kernelX.push_back(-1);
	kernelX.push_back(1); kernelX.push_back(0); kernelX.push_back(-1);

	/*
	|-1  -1  -1|   1
	| 0   0   0| * -  =  Ky
	| 1   1   1|   3
	*/
	kernelY.push_back(-1); kernelY.push_back(-1); kernelY.push_back(-1);
	kernelY.push_back(0); kernelY.push_back(0); kernelY.push_back(0);
	kernelY.push_back(1); kernelY.push_back(1); kernelY.push_back(1);

	division = 3.0f;

	convolution.SetKernel(kernelX, division, 3, 3);
	convolution.DoConvolution(sourceImage, dx);
	convolution.SetKernel(kernelY, division, 3, 3);
	convolution.DoConvolution(sourceImage, dy);

	destinationImage = Mat(sourceImage.rows, sourceImage.cols, CV_8UC1, Scalar(0));
	int rowStep = sourceImage.cols;

	short* pRowX = (short*)(dx.data);
	short* pRowY = (short*)(dy.data);
	uchar* pRow = destinationImage.data;
	int threshold = 1024;

	for (int i = 0; i < sourceImage.rows; i++, pRowX += rowStep, pRowY += rowStep, pRow += rowStep)
	{
		short* pDataX = pRowX;
		short* pDataY = pRowY;
		uchar* pData = pRow;
		for (int j = 0; j < sourceImage.cols; j++, pDataX++, pDataY++, pData++)
			if (*pDataX * *pDataX + *pDataY * *pDataY >= threshold)
				*pData = 255;
	}

	return 0;
}

bool Exist(Mat S, int x, int y, int _highThreshold)
{
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if (S.at<short>(x + i, y + j) >= _highThreshold)
				return true;
	return false;
}

int detectByCany(const Mat& srcImage, Mat& dstImage, int _lowThreshold, int _highThreshold)
{
	if (empty(srcImage))
	{
		return 0;
	}

	Mat Gauss(srcImage.rows, srcImage.cols, CV_8UC1, Scalar(0));
	Blur B;
	//Làm mờ ảnh bằng Gauss
	B.BlurImage(srcImage, Gauss, 5, 5, 2);

	Mat S(srcImage.rows, srcImage.cols, CV_16SC1, Scalar(0)); //Ảnh đạo hàm của ảnh Gauss
	Mat angle(srcImage.rows, srcImage.cols, CV_32FC1, Scalar(0)); //Ma trận góc

	//Tính đạo hàm theo hướng x, y sau khi làm trơn
	Convolution convolution;
	vector<int> kernelX;
	vector<int> kernelY;
	float division = 1.0f;
	Mat dx, dy;

	/*
	|1  0  -1|   1
	|2  0  -2| * -  =  Kx
	|1  0  -1|   4
	*/
	kernelX.push_back(1); kernelX.push_back(0); kernelX.push_back(-1);
	kernelX.push_back(2); kernelX.push_back(0); kernelX.push_back(-2);
	kernelX.push_back(1); kernelX.push_back(0); kernelX.push_back(-1);

	/*
	|-1  -2  -1|   1
	| 0   0   0| * -  =  Ky
	| 1   2   1|   4
	*/
	kernelY.push_back(-1); kernelY.push_back(-2); kernelY.push_back(-1);
	kernelY.push_back(0); kernelY.push_back(0); kernelY.push_back(0);
	kernelY.push_back(1); kernelY.push_back(2); kernelY.push_back(1);

	division = 4.0f;

	convolution.SetKernel(kernelX, division, 3, 3);
	convolution.DoConvolution(Gauss, dx);
	convolution.SetKernel(kernelY, division, 3, 3);
	convolution.DoConvolution(Gauss, dy);

	//Tính ma trận góc:
	for (int i = 1; i < angle.rows - 1; i++)
	{
		for (int j = 1; j < angle.cols - 1; j++)
		{
			short a = dy.at<short>(i, j);
			short b = dx.at<short>(i, j);

			if (a > 0 && b == 0)
				angle.at<float>(i, j) = 90;
			else if (a < 0 && b == 0)
				angle.at<float>(i, j) = -90;
			else if (a == 0 && b == 0)
				angle.at<float>(i, j) = 0;
			else
				angle.at<float>(i, j) = (float)(atan(a / b) * 180 / PI);
		}
	}

	//Tính S(x, y) = sqrt(Sx ^ 2 + Sy ^ 2)
	for (int i = 0; i < S.rows; i++)
		for (int j = 0; j < S.cols; j++)
			S.at<short>(i, j) = (short)sqrt(dx.at<short>(i, j) * dx.at<short>(i, j) + dy.at<short>(i, j) * dy.at<short>(i, j));

	//Chuẩn hóa về 4 bin: 0 | 45 | 90 | 135
	for (int i = 1; i < angle.rows - 1; i++)
	{
		for (int j = 1; j < angle.cols - 1; j++)
		{
			float a = angle.at<float>(i, j);

			if (a <= 22.5 || a > 157.5 || a >= -22.5 || a < -157.5)
				angle.at<float>(i, j) = 0;
			else if ((a > 22.5 && a <= 67.5) || (a > -157.5 && a <= -112.5))
				angle.at<float>(i, j) = 45;
			else if ((a > 67.5 && a <= 112.5) || (a > -112.5 && a <= -67.5))
				angle.at<float>(i, j) = 90;
			else if ((a > 112.5 && a <= 157.5) || (a > -67.5 && a <= -22.5))
				angle.at<float>(i, j) = 135;
		}
	}

	//Loại trừ dựa trên các điểm lân cận và hướng đạo hàm
	for (int i = 1; i < angle.rows - 1; i++)
	{
		for (int j = 1; j < angle.cols - 1; j++)
		{
			int a = (int)angle.at<float>(i, j);

			if (a == 0)
			{
				short s1 = S.at<short>(i, j + 1);
				short s2 = S.at<short>(i, j - 1);
				short s = S.at<short>(i, j);
				if (s != MAX(MAX(s, s1), s2))
					S.at<short>(i, j) = 0;
			}
			else if (a == 45)
			{
				short s1 = S.at<short>(i + 1, j - 1);
				short s2 = S.at<short>(i - 1, j + 1);
				short s = S.at<short>(i, j);
				if (s != MAX(MAX(s, s1), s2))
					S.at<short>(i, j) = 0;
			}
			else if (a == 90)
			{
				short s1 = S.at<short>(i - 1, j);
				short s2 = S.at<short>(i + 1, j);
				short s = S.at<short>(i, j);
				if (s != MAX(MAX(s, s1), s2))
					S.at<short>(i, j) = 0;
			}
			else if (a == 135)
			{
				short s1 = S.at<short>(i - 1, j - 1);
				short s2 = S.at<short>(i + 1, j + 1);
				short s = S.at<short>(i, j);
				if (s != MAX(MAX(s, s1), s2))
					S.at<short>(i, j) = 0;
			}
		}
	}

	//Lọc ngưỡng
	Mat DesImage(S.rows, S.cols, CV_8UC1, Scalar(0));
	for (int i = 0; i < S.rows; i++)
	{
		for (int j = 0; j < S.cols; j++)
		{
			//cout << S.at<short>(i, j) << endl;
			if (S.at<short>(i, j) >= _lowThreshold && S.at<short>(i, j) <= _highThreshold)
				if (Exist(S, i, j, _highThreshold)) DesImage.at<uchar>(i, j) = 255;
				else if (S.at<short>(i, j) >= _highThreshold)
					DesImage.at<uchar>(i, j) = 255;
				else
					DesImage.at<uchar>(i, j) = 0;
		}
	}
	dstImage = DesImage;
	return 1;
}