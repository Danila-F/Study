#pragma once

#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <assert.h>
#include <math.h>

#define PI 3.14159265358979323846f

using namespace std;
using namespace cv;

class Convolution
{
	vector<int> _kernel;  //Lưu giá trị của ma trận kernel dùng để tích chập
	float _division;  //Nhân tử chung của kernel: 1/_division
	int _kernelWidth;  //Chiều rộng (ngang) kernel
	int _kernelHeight;  //Chiều cao (dọc) kernel
public:
	//Trả về kernel
	vector<int> GetKernel();
	//Set kernel, chiều rộng và chiều cao phải là số lẻ
	void SetKernel(vector<int> kernel, float division, int kernelWidth, int kernelHeight);

	/*
	Hàm tính convolution của một ảnh xám với kernel được xác định trước
	sourceImage: ảnh input
	destinationImage: ảnh output
	Hàm trả về:
		0: nếu tính thành công
		1: nếu tính thất bại (không đọc được ảnh input,...)
	*/
	int DoConvolution(const Mat& sourceImage, Mat& destinationImage);
	Convolution();
	~Convolution();
};

class Blur
{
public:
	/*
	Hàm lọc nhiễu ảnh xám
		sourceImage: ảnh input
		destinationImage: ảnh output
	method: phương pháp lọc nhiễu
		0: trung bình
		1: trung vị
		2: Gaussian
	Hàm trả về:
		0: nếu lọc nhiễu thành công
		1: nếu lọc nhiễu thất bại (không đọc được ảnh input,...)
	*/
	int BlurImage(const Mat& sourceImage, Mat& destinationImage, int kernelWidth, int kernelHeight, int method);
	Blur();
	~Blur();
};

int detectByLaplace(const Mat& sourceImage, Mat& destinationImage);
int detectBySobel(const Mat& sourceImage, Mat& destinationImage);
int detectByPrewitt(const Mat& sourceImage, Mat& destinationImage);
int detectByCany(const Mat& srcImage, Mat& dstImage, int _lowThreshold, int _highThreshold);