#include "Header.h"

Blur::Blur()
{
}

Blur::~Blur()
{
}

int Blur::BlurImage(const Mat& sourceImage, Mat& destinationImage, int kernelWidth, int kernelHeight, int method)
{
	//Nếu ảnh input rỗng => không làm gì hết
	if (sourceImage.empty())
		return 1;

	/*
	Nếu là method 1, lọc phi tuyến, không dùng được nhân chập
	Duyệt tất cả lân cận của điểm ảnh (i, j)
	Sắp xếp lại và lấy giá trị ở giữa gán cho điểm ảnh (i, j)
	Thao tác duyệt tương tự hàm nhân chập (đọc comment hàm nhân chập để hiểu cách duyệt)
	*/
	if (method == 1)
	{
		destinationImage = Mat(sourceImage.rows, sourceImage.cols, CV_8UC1, Scalar(0));
		int rowStep = sourceImage.cols;

		int halfHeigth = kernelHeight / 2;
		int halfWidth = kernelWidth / 2;

		uchar* pRowSrc = sourceImage.data + rowStep * halfHeigth + halfWidth;
		uchar* pRowDst = destinationImage.data + rowStep + halfHeigth + halfWidth;

		for (int i = halfHeigth; i < sourceImage.rows - halfHeigth; i++, pRowSrc += rowStep, pRowDst += rowStep)
		{
			uchar* pDataSrc = pRowSrc;
			uchar* pDataDst = pRowDst;
			for (int j = halfWidth; j < sourceImage.cols - halfWidth; j++, pDataSrc++, pDataDst++)
			{
				vector<uchar> value;
				for (int u = -halfHeigth; u <= halfHeigth; u++)
					for (int v = -halfWidth; v <= halfWidth; v++)
						value.push_back(pDataSrc[-u * rowStep - v]);

				sort(value.begin(), value.end());
				*pDataDst = value[value.size() / 2];
			}
		}

		return 0;
	}

	//Thực hiện phép nhân chập với method 0 và method 2
	Convolution convolution;
	vector<int> kernel;
	Mat blured;
	float division = 1.0f;

	//Tạo kernel nhân chập
	if (method == 0)
	{
		//Mỗi phần tử kernel có giá trị = 1
		//Nhân tử chung kernel là 1/(tổng số phần tử) => division = tổng số phần tử
		division = (float)(kernelHeight * kernelWidth);
		for (int i = 0; i < division; i++)
			kernel.push_back(1);
	}
	else if (method == 2)
	{
		/*
		Mặc định sigma = 1
		Mỗi phần tử kernel có chỉ số là (u, v) với:
			-halfHeight <= u <= halfHeight
			-halfWidth <= v <= halfWidth
		Tính trước các giá trị:
			sigma22 = 2 x sigma^2
			PIsigma22 = 2 x PI x sigma^2
		Rời rạc hóa kernel số thực thành kernel số nguyên kèm nhân tử chung kernel
		*/
		vector<float> fKernel;
		float sigma = 1.0f;
		float sigma22 = 2 * sigma * sigma;
		float PIsigma22 = PI * sigma22;

		int halfHeight = kernelHeight / 2;
		int halfWidth = kernelWidth / 2;

		for (int u = -halfHeight; u <= halfHeight; u++)
			for (int v = -halfWidth; v <= halfWidth; v++)
				fKernel.push_back(exp(-(u * u + v * v) / sigma22) / PIsigma22);

		division = 0.0f;
		for (int i = 0; i < (int)(fKernel.size()); i++)
		{
			int value = (int)round(fKernel[i] / fKernel[0]);
			division += value;
			kernel.push_back(value);
		}
	}

	convolution.SetKernel(kernel, division, kernelWidth, kernelHeight);
	convolution.DoConvolution(sourceImage, blured);

	/*
	Kết quả phép nhân chập là ảnh có dạng CV_16SC1, phải chuyển về dạng CV_8UC1 để lưu và hiển thị ra
	Thao tác duyệt tương tự hàm nhân chập (đọc comment hàm nhân chập để hiểu cách duyệt)
	*/
	destinationImage = Mat(sourceImage.rows, sourceImage.cols, CV_8UC1, Scalar(0));
	int rowStep = sourceImage.cols;

	short* pRowBlr = (short*)(blured.data);
	uchar* pRow = destinationImage.data;

	for (int i = 0; i < sourceImage.rows; i++, pRowBlr += rowStep, pRow += rowStep)
	{
		short* pDataBlr = pRowBlr;
		uchar* pData = pRow;
		for (int j = 0; j < sourceImage.cols; j++, pDataBlr++, pData++)
			*pData = (uchar)(*pDataBlr);
	}

	return 0;
}