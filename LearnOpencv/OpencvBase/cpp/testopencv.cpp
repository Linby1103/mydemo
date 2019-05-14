#include "testopencv.h"
#include <windows.h>
#include <sstream>
//图像的平移
#define rad CV_PI/180
void Proceimg::movePiexl(int x_len, int y_len, cv::Mat& srcimg)
{
	cv::Mat procimg,resultimg;
	if (srcimg.channels() == 3) cvtColor(srcimg, procimg, CV_BGR2BGRA);
	else	procimg = srcimg;
	resultimg.create(Size(srcimg.cols, srcimg.rows), srcimg.depth());
	if (!procimg.data)
	{
		printf("Image is Empty!");
		return;
	}
	for (int idy = 0; idy < procimg.rows; ++idy)
	{
		for (int idx = 0; idx < procimg.cols; ++idx)
		{
			if ((idy - y_len >= 0) && (idy - y_len < procimg.rows) && (idx - x_len >= 0) && (idx - x_len < procimg.rows))
			{
				uchar ch0 = procimg.at<uchar>(idy - y_len, idx - x_len);
				resultimg.at<uchar>(idy, idx) = ch0;
			}
			else
				resultimg.at<uchar>(idy, idx) = 255;
		}
	}
	srcimg = resultimg;
	resultimg.release();
}
//水平镜像变换
void Proceimg::imgHorMairror(cv::Mat& srcimg)
{
	cv::Mat grayimg, resultimg;
	if (srcimg.channels() == 3) cvtColor(srcimg, grayimg, CV_BGR2BGRA);
	else grayimg = srcimg;
	resultimg.create(srcimg.size(), srcimg.depth());
	for (int idy = 0; idy < grayimg.rows; ++idy)
	{
		uchar *ptr = grayimg.ptr<uchar>(idy);
		uchar *res_ptr = resultimg.ptr<uchar>(idy);
		for (int idx = 0; idx < grayimg.cols; ++idx)
		{
			uchar piexl = ptr[idx];
			res_ptr[resultimg.cols - 1 - idx] = piexl;
		}
	}
	srcimg = resultimg;
	resultimg.release();
}
void MatrixTransposition(cv::Mat& srcimg)
{
	cv::Mat proimg,grayimg;
	cv::Mat Matrix;
	if (srcimg.channels() == 3) cvtColor(srcimg, Matrix, CV_BGR2BGRA);
	else Matrix = srcimg;
	proimg.create(Matrix.size(), Matrix.depth());
	if (!Matrix.data)
	{
		printf("@Image is Null!");
		return;
	}
	for (int i = 0; i < Matrix.rows; ++i)
	{
		for (int j = 0; j < Matrix.cols; ++j)
		{
			proimg.at<uchar>(i, j) = Matrix.at<uchar>(j, i);
		}
	}
	srcimg = proimg;
	proimg.release();
}

void Proceimg::imgVerHorMairror(cv::Mat& srcimg)
{
	cv::Mat grayimg, resultimg;
	if (srcimg.channels() == 3) cvtColor(srcimg, grayimg, CV_BGR2BGRA);
	else grayimg = srcimg;
	resultimg.create(srcimg.size(), srcimg.depth());
	for (int idy = 0; idy < grayimg.rows; ++idy)
	{
		uchar *ptr = grayimg.ptr<uchar>(grayimg.rows-1-idy);
		uchar *res_ptr = resultimg.ptr<uchar>(idy);
		for (int idx = 0; idx < grayimg.cols; ++idx)
		{
			uchar piexl = ptr[idx];
			res_ptr[resultimg.cols - 1 - idx] = piexl;
		}
	}
	srcimg = resultimg;
	resultimg.release();
}
bool Proceimg::ImageRotate(cv::Mat& srcimg, const double angle, cv::Point rotatecen)
{
	cv::Point center = rotatecen;
	cv::Mat grayimg, resultimg;
	if (srcimg.empty())
		return false;
	if (center.x<0 || center.x>srcimg.cols - 1)
		center.x = 0;
	if (center.y<0 || center.y>srcimg.rows - 1)
		center.y = 0;
	if (srcimg.channels() == 1)  grayimg = srcimg;
	else cvtColor(srcimg, grayimg, CV_BGR2GRAY);
	
	resultimg.create(grayimg.size(), grayimg.depth());
	int img_height = grayimg.rows;
	int img_width = grayimg.cols;
	int xOffset = static_cast<int>(-0.5*img_width*cos(angle*rad) - 0.5*img_height*sin(angle*rad) + 0.5*img_width);
	int yOffset = static_cast<int>(0.5*img_width*sin(angle*rad) - 0.5*img_height*cos(angle*rad) - 0.5*img_height);
	for (int i1 = 0; i1 < resultimg.rows; i1++)
	{
		for (int j1 = 0; j1 < resultimg.cols; j1++)
		{
			int i0 = static_cast<int>(i1*cos(angle*rad) + j1*sin(angle*rad) + xOffset);
			int j0 = static_cast<int>( -i1*sin(angle*rad) + j1*cos(angle*rad) + yOffset);
			if (i0 <= 0 || i0>img_width - 1 || j0>img_height - 1 || j0 < 0)
				resultimg.at<uchar>(i1, j1) = 0;
			else resultimg.at<uchar>(i1, j1) = grayimg.at<uchar>(i0, j0);
		}
	}
	srcimg = resultimg.clone();
	resultimg.release();
	return true;
}
bool Proceimg::ImageRotate(cv::Mat& srcimg, const double angle)
{
	if (srcimg.empty() || angle < 1e-6)
	{
		printf("Image is Null or angle Illegal!");
		return -1;
	}
	cv::Mat grayimg,resultimg;
	if (srcimg.channels() == 3) cvtColor(srcimg, grayimg, CV_BGR2GRAY);
	else grayimg = srcimg;
	ImageShow("debug", grayimg);
	resultimg.create(grayimg.size(), grayimg.depth());
	for (int i = 0; i < grayimg.rows; i++)
	{
		for (int j = 0; j < grayimg.cols; j++)
		{
			int xpos = static_cast<int>(i*cos(angle*CV_PI / 180)+j*sin(angle*CV_PI/180) + 0.5f);
			int ypos = static_cast<int>(j*cos(angle*CV_PI / 180) -i*sin(angle*CV_PI/180)+0.5f);
			if (xpos<0 || xpos>grayimg.cols-1 || ypos<0 || ypos>grayimg.rows-1)
				resultimg.at<uchar>(i, j)=(uchar)0;
			else resultimg.at<uchar>(i, j) = grayimg.at<uchar>(xpos, ypos);
		}
	}
	srcimg = resultimg;
	resultimg.release();
	return true;
}
void Proceimg::imgVerMairror(cv::Mat& srcimg)
{
	cv::Mat grayimg, resultimg;
	if (srcimg.channels() == 3) cvtColor(srcimg, grayimg, CV_BGR2BGRA);
	else grayimg = srcimg;
	resultimg.create(srcimg.size(), srcimg.depth());
	for (int idy = 0; idy < grayimg.rows; ++idy)
	{
		uchar *ptr = grayimg.ptr<uchar>(idy);
		uchar *res_ptr = resultimg.ptr<uchar>(grayimg.cols - 1 - idy);
		for (int idx = 0; idx < grayimg.cols; ++idx)
		{
			uchar piexl = ptr[idx];
			res_ptr[idx] = piexl;
		}
	}
	srcimg = resultimg;
	resultimg.release();
}
//线性插值算法--->图片缩放+插值
void Proceimg::getgrayMat(cv::Mat &colorimg)
{
	cv::Mat grayimg;
	if (colorimg.channels() != 1)
	{
		cvtColor(colorimg, grayimg, CV_BGR2GRAY);
		colorimg = grayimg;
	}
	else return;
}
void Proceimg::ImageZoom(cv::Mat &srcimg, cv::Mat &dst, float scale)
{
	cv::Mat resultimg, grayimg;
	if (scale <= 1e-6)
	{
		cout << "Illegal Parameter!" << endl;
		return;
	}
	if (!srcimg.data)
	{
		cout << "Image Is Null!" << endl;
		return;
	}
	
	grayimg = srcimg.clone();
	int new_width = static_cast<int>(scale*srcimg.cols);
	int new_height = static_cast<int>(scale*srcimg.rows);
	getgrayMat(grayimg);
	resultimg.create(cv::Size(new_width, new_height), grayimg.depth());
	for (int i0 = 0; i0 < new_height; i0++)
	{
		for (int j0 = 0; j0 < new_width; j0++)
		{
				float j1 = (j0+0.1f) / scale;
				float i1 = (i0+0.1f )/ scale;
				if (j1 <= 1e-6)
					j1 = 0.f;
				if (i1 <= 1e-6)
					i1 = 0.f;
				uchar Interval=InterBilinear(i1, j1, grayimg);
				resultimg.at<uchar>(i0, j0) = Interval;
		}
	}
	dst = resultimg.clone();
	resultimg.release();
}


uchar Proceimg::InterBilinear(float x,float y,cv::Mat &src)
{
	int x_L = cvFloor(x) - 1;
	int x_R = cvFloor(x) + 1;
	int y_T = cvFloor(y) - 1;
	int y_B = cvFloor(y) + 1;

	if (x_L <= 0) x_L = 0;
	else if (x_L >= src.cols - 1) x_L = src.cols - 1;
	if (x_R <= 0) x_R = 0;
	else if (x_R > src.cols - 1) x_R = src.cols - 1;
		
	if (y_T <= 0) y_T = 0;
	else if (y_T > src.rows - 1) y_T = src.rows - 1;
	if (y_B <= 0) y_B = 0;
	else if (y_B > src.rows - 1) y_B = src.rows - 1;

	uchar grayTopL = src.at<uchar>(x_L, y_T);//左上角
	uchar grayTopR = src.at<uchar>(x_R, y_T);//右上角
	uchar grayBottonL = src.at<uchar>(x_L, y_B);//左下角
	uchar grayBottonR = src.at<uchar>(x_R, y_B);//右下角
	//1、计算X方向插值
	float HLscale = 0.f, HRscale = 0.f, VTscale = 0.f, VBscale=0.f;
	HLscale = 1 - (x - x_L) / (x_R - x_L);
	HRscale = 1 - (x_R - x) / (x_R - x_L);
	VTscale = 1 - (y - y_T) / (y_B - y_T);
	VBscale = 1 - (y_B-y) / (y_B - y_T);
	uchar Hpixel1= static_cast<uchar>(grayTopL*HLscale + grayTopR*HRscale);
	uchar Hpixel2 = static_cast<uchar>(grayBottonL*HLscale + grayBottonR*HRscale);
	//计算Y方向插值
	uchar Vpixel = static_cast<uchar>(Hpixel1*VTscale + Hpixel2*VBscale);
	return Vpixel;
}
//滤波
void Proceimg::ImageFilter(cv::Mat &srcimg, int kerneltype)
{
	if(!srcimg.data)
	{
		printf("Image Is Empty!\n");
		return;
	}
	cv::Mat graymat;
	//threshold(srcimg, graymat, 100, 190, THRESH_BINARY_INV);
	graymat = srcimg.clone();
	cv::Mat Kernel,result;
	float fCoef = 0.f;
	float ConSum = 0;
	getgrayMat(graymat);
	result.create(graymat.size(), graymat.depth());
	switch (kerneltype)
	{
	case 0://平均平滑 
		Kernel = (Mat_<char>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1);
		break;
	case 1://高斯平滑
		Kernel = (Mat_<char>(3, 3) << 1, 2, 1, 2, 4, 2, 1, 2, 1);
		break;

	case 2://sobel水平边缘检测 
		Kernel = (Mat_<char>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
		break;
	case 3://sobel垂直边缘检测
		Kernel = (Mat_<char>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
		break;

	case 4://Log边缘检测 
		Kernel = (Mat_<char>(5, 5) << 0, 0, -1, 0, 0, 
			                            0,-1, -2, -1, 0,
										-1,-2,16,-2,-1,
										0,-1,-2,-1,0,
										0,0,-1,0,0);
		break;
	case 5://Laplacian
		Kernel = (Mat_<char>(3, 3) << 0, 1, 0, 1, -4, 1, 0, 1, 0);
		break;
	case 6://Laplacian
		Kernel = (Mat_<char>(3, 3) << -1, -1, -1, -1, 8, -1, -1, -1, -1);
		break;
	}
	for (int i = 1; i < graymat.rows-1; i++)
	{
		for (int j = 1; j < graymat.cols-1; j++)
		{
			for (int m = 0; m < Kernel.rows; m++)
			{
				for (int n = 0; n < Kernel.cols; n++)
				{
					ConSum += static_cast<float>(Kernel.at<char>(m, n)*graymat.at<uchar>(i + m - 1, j + n - 1));
				}
			}
			
		//	printf("piexl=%d", ConSum);
			if (ConSum < 1e-6) ConSum = 0;
			if (ConSum>255) ConSum = 255;
			result.at<uchar>(i, j) = (uchar)(ConSum);
			ConSum = 0;
		}
	}
	
	printf("complete!\n");
	srcimg = result.clone();
	result.release();
}
//均值滤波
void Proceimg::meanfilter(cv::Mat& src)
{
	if (src.empty())
	{
		printf("Image is Null!\n");
		return;
	}
	float grauval = 0.f;
	cv::Mat result;
	result.create(src.size(), src.depth());
	for (int i = 1; i < src.rows-1; i++)
	{
		for (int j = 1; j < src.cols-1; j++)
		{
			grauval = static_cast<float>(src.at<uchar>(i - 1, j - 1) + src.at<uchar>(i, j - 1) + src.at<uchar>(i + 1, j - 1)\
				+ src.at<uchar>(i - 1, j)  + src.at<uchar>(i + 1, j)\
				+ src.at<uchar>(i - 1, j + 1) + src.at<uchar>(i, j + 1) + src.at<uchar>(i + 1, j + 1)) / 9.0f;
			if (grauval>255) grauval = 255;
			if (grauval < 0) grauval = 0;
			result.at<uchar>(i, j) = (uchar)grauval;
		}
	}
	src = result.clone();
	result.release();
}
//signal channels
uchar comparmax(uchar val, uchar vbl)
{
	return val < vbl;
}
#define THRESHOLD 20
void Proceimg::AdaptFilter(cv::Mat& src)
{
	cv::Mat Kernel = (Mat_<float>(3, 3) << 1.0/16.0, 2.0/16.0, 1.0/16.0, 2.0/16.0, 4.0/16.0, 2.0/16.0, 1.0/16.0, 2.0/16.0, 1.0/16.0);
	if (src.empty())
	{
		printf("Image is Null!\n");
		return;
	}
	float grauval;
	cv::Mat result;
	vector<uchar> regiondata;
	result.create(src.size(), src.depth());
	for (int i = 1; i < src.rows - 1; ++i)
	{
		
		for (int j = 1; j < src.cols - 1; ++j)
		{
			regiondata.clear();
			regiondata.push_back(src.at<uchar>(i - 1, j - 1));
			regiondata.push_back(src.at<uchar>(i - 1, j));
			regiondata.push_back(src.at<uchar>(i - 1, j + 1));
			regiondata.push_back(src.at<uchar>(i - 1, j));
			regiondata.push_back(src.at<uchar>(i , j ));
			regiondata.push_back(src.at<uchar>(i + 1, j ));
			regiondata.push_back(src.at<uchar>(i - 1, j +1));
			regiondata.push_back(src.at<uchar>(i , j +1));
			regiondata.push_back(src.at<uchar>(i + 1, j + 1));
			sort(regiondata.begin(), regiondata.end(), comparmax);
			int compres =abs( (int)regiondata[0] - (int)regiondata[8]);
			
			if (compres -70 > 0)
			{
				grauval = 0;
				for (int k = 0; k < Kernel.rows; k++)
				{
					for (int l = 0; l < Kernel.cols; l++)
					{
						float ker = Kernel.at<float>(k, l);
						uchar srcpiex = src.at<uchar>(i + k - 1, j + l - 1);
						grauval += ker*srcpiex;
					}
				}
				result.at<uchar>(i, j) = (uchar)grauval;
			}
			else
			{
				result.at<uchar>(i, j) = src.at<uchar>(i, j);
			}
		}
	}
	src = result.clone();
	result.release();
}
void Proceimg::medialFilter(cv::Mat &src)
{
	if (!src.data){ printf("Source Image is NULL!\n"); return; }
	cv::Mat result;
	vector<uchar> regiondata;
	result.create(src.size(), src.depth());
	for (int i = 1; i < src.rows-1; ++i)
	{
		for (int j = 1; j < src.cols-1; ++j)
		{

			regiondata.clear();
			for (int l = 0; l < 3; l++)
			{
				for (int k = 0; k < 3; k++)
				{
					regiondata.push_back(src.at<uchar>(i+l-1, k+j-1));
				}
			}
			sort(regiondata.begin(), regiondata.end(), comparmax);
			result.at<uchar>(i, j) = regiondata[(3 * 3 - 1) / 2];
		}
	}
	src = result.clone();
	result.release();
}

void Proceimg::AdvmedialFilter(cv::Mat &src)
{
	if (!src.data){ printf("Source Image is NULL!\n"); return; }
	cv::Mat result;
	vector<uchar> regiondata;
	result.create(src.size(), src.depth());
	for (int i = 1; i < src.rows - 1; ++i)
	{
		for (int j = 1; j < src.cols - 1; ++j)
		{

			regiondata.clear();
			for (int l = 0; l < 3; l++)
			{
				for (int k = 0; k < 3; k++)
				{
					regiondata.push_back(src.at<uchar>(i + l - 1, k + j - 1));
				}
			}
			sort(regiondata.begin(), regiondata.end(), comparmax);
			if (src.at<uchar>(i, j)>regiondata[0] || src.at<uchar>(i, j)>regiondata[(3 * 3 - 1) / 2])
				result.at<uchar>(i, j) = regiondata[(3 * 3 - 1) / 2];
			else
				result.at<uchar>(i, j) = src.at<uchar>(i, j);
		}
	}
	src = result.clone();
	result.release();
}
//需要填充图像的边界
void Proceimg::AdaptmedialFilter(cv::Mat &src, int img_x, int img_y, int kernelsize, int kernelmax,uchar &piexlval)
{
	//Mat proceimg;
	
	std::vector<uchar> piexls;
	//proceimg.create(src.size(), src.depth());
	if (!src.data)
	{
		printf("Iamge is Empty!\n");
		return;
	}
	if (img_x<0 || img_x>src.cols-1 || img_y<0 || img_y>src.rows-1)
	{
		printf("invalid value!");
		return;
	}
	piexls.clear();

	for (int i = -kernelsize/2; i <= kernelsize/2; ++i)
	{
		for (int j = -kernelsize / 2; j <= kernelsize / 2; ++j)
		{
			piexls.push_back(src.at<uchar>(img_y + i, img_x + j));
		}
	}

	sort(piexls.begin(), piexls.end(), comparmax);
	uchar media = piexls[kernelsize*kernelsize / 2];
	uchar maxpiexl = piexls[kernelsize*kernelsize-1];
	uchar minpiexl = piexls[0];
	uchar cur_piexl = src.at<uchar>(img_y, img_x);

	if (media - minpiexl>0 && media - maxpiexl < 0)//A非噪声点
	{
        if (cur_piexl - minpiexl>0 && cur_piexl - maxpiexl < 0)//B   /*结束条件*/
		{
			piexlval = cur_piexl;
			return;
		}
		else//当前点是噪声用中值代替
		{
			piexlval = media;
			return;
		}
	}
#if 1
	else//中值是噪声点 扩大搜索窗口的尺寸
	{
		kernelsize += 2;
		if (kernelsize > kernelmax)
		{
			piexlval = media;
			return;
		}
		AdaptmedialFilter(src, img_x, img_y, kernelsize, kernelmax, piexlval);//递归本身
	}
#endif
	//proceimg.release();
}

/**
*  Author:LiBin
*  Description:基于Lalacian的锐化算子
*  @param  src：源图像(单通道/3通道)
*  @param  dst:目标图像
*  @return:无
**/
void EnhanceFilter(cv::Mat &src, cv::Mat &dst, float coef,float A=1.3)
{
	bool color = true;
	if (!src.data)
	{
		printf("image data is empty!\n");
		return;
	}
	cv::Mat cv8uc3mat;
	if (src.channels() ==1)
		color=false;
	cv::Mat kernel = (Mat_<float>(3, 3) << 0, 1, 0, 1, -4, 1, 0, 1, 0);
	cv::Mat result;
	result.create(src.size(), CV_8UC3);
	float sumfilterch_n1, sumfilterch_n2, sumfilterch_n3;
	for (int i = 1; i < src.rows - 1; i++)
	{
		//uchar *ptr1 = src.ptr<uchar>(i);
		for (int j = 1; j < src.cols - 1; j++)
		{
			sumfilterch_n1= sumfilterch_n2= sumfilterch_n3 = 0.f;
			if (color)
			{
				for (int m = 0; m < kernel.rows; ++m)
				{
					for (int n = 0; n < kernel.cols; ++n)
					{
						sumfilterch_n1 += static_cast<float>(kernel.at<float>(m, n)* src.at<Vec3b>(i + m - 1, j + n - 1)[0]);
						sumfilterch_n2 += static_cast<float>(kernel.at<float>(m, n)* src.at<Vec3b>(i + m - 1, j + n - 1)[1]);
						sumfilterch_n3 += static_cast<float>(kernel.at<float>(m, n)* src.at<Vec3b>(i + m - 1, j + n - 1)[2]);
					}
				}
				int src_ch1 = A*src.at<Vec3b>(i, j)[0] - sumfilterch_n1;
				int src_ch2 = A*src.at<Vec3b>(i, j)[1] - sumfilterch_n2;
				int src_ch3 = A*src.at<Vec3b>(i, j)[2] - sumfilterch_n3;
				
				if (src_ch1>255) src_ch1 = 255;
				else if (src_ch1 < 1e-6) src_ch1 = 0;

				if (src_ch2>255) src_ch2 = 255;
				else if (src_ch2 < 1e-6) src_ch2 = 0;

				if (src_ch3>255) src_ch3 = 255;
				else if (src_ch3 < 1e-6) src_ch3 = 0;
				
				result.at<Vec3b>(i, j)[0] = static_cast<uchar>(src_ch1);
				result.at<Vec3b>(i, j)[1] = static_cast<uchar>(src_ch2);
				result.at<Vec3b>(i, j)[2] = static_cast<uchar>(src_ch3);
			}
			else
			{
				src.convertTo(cv8uc3mat, CV_8UC1);
				for (int m = 0; m < kernel.rows; ++m)
				{
					for (int n = 0; n < kernel.cols; ++n)
					{
						sumfilterch_n1 += static_cast<float>(kernel.at<char>(m, n)* src.at<uchar>(i + m - 1, j + n - 1));
					}
				}

				sumfilterch_n1 *= coef;
				int src_ch = A*src.at<uchar>(i, j) - sumfilterch_n1;
				if (src_ch>255) src_ch = 255;
				else if (src_ch < 1e-6) src_ch = 0;
				result.at<uchar>(i, j) = static_cast<uchar>(src_ch);
			}
		}
	}
	dst = result.clone();
	result.release();
}
void Proceimg::filter(cv::Mat& src, cv::Mat &dst, FilterMethod method)
{
	if (!src.data)
	{
		printf("Image data is NULL!\n");
		return ;
	}
	cv::Mat colorgray = src.clone();
    getgrayMat(colorgray);
	switch (method)
	{
	case 0:
		meanfilter(colorgray);
		break;
	case 1:
		AdaptFilter(colorgray);
		break;
	case 2:
		//AdaptmedialFilter(colorgray);
		;
		//medialFilter(colorgray);
		break;
	}
	dst = colorgray;
}
void boderexpand(cv::Mat &src)
{
	if (src.empty())
	{
		printf("Source Image is Invalid!\n");
		return;
	}
	//边缘扩展
	Proceimg pro;
	cv::Mat dst,graymat,result;
	
	int kernelminsize = 3;
	int kernelmaxsize = 9;
	uchar piexls = '0';
	if (src.depth() != 1) cvtColor(src, graymat, cv::COLOR_BGR2GRAY);
	else graymat = dst.clone();
	cv::copyMakeBorder(graymat, dst, kernelminsize, kernelminsize, kernelminsize, kernelminsize, cv::BORDER_REFLECT);
	result.create(dst.size(), CV_8UC1);
	for (int i = kernelmaxsize / 2; i < src.rows - kernelmaxsize / 2 - 1; i++)
	{
		for (int j = kernelmaxsize / 2; j < src.cols - kernelmaxsize / 2 - 1; j++)
		{
			pro.AdaptmedialFilter(dst, j, i, kernelminsize, kernelmaxsize, piexls);
			result.at<uchar>(i, j) = piexls;
		}
	}
	imshow("adaptmedia", result);
	waitKey(0);
	result.release();
}
//////////////////////////////////////////////////////////////////////////////////////
//Canny算子实现
//1、产生高斯核
void GaussKernel(std::vector<double> &kernel, double sigam, int kernelsize = 3)
{
	if (!kernelsize % 2) return;
	vector<double> tmpkernel;
	int Ex = kernelsize / 2;
	//tmpkernel.resize(kernelsize*kernelsize);
	if (!kernelsize / 2) return;
	double sum = 0.f;
	for (int i = 0; i < kernelsize; ++i)
	{
		for (int j = 0; j < kernelsize; ++j)
		{
			double ele = 1 / (2 * CV_PI*(sigam*sigam))*exp(-((i - Ex)*(i - Ex) + (j - Ex)*(j - Ex)) / (sigam*sigam));
			sum += ele;
			tmpkernel.push_back(ele);
		}
	}

	
	for (int k = 0; k < tmpkernel.size(); k++)
	{
		kernel.push_back(tmpkernel[k] / sum);
		
	}
}
void GaussFilter(cv::Mat &src,int kernelsize,double sigma)
{
	if (!src.data)
	{
		return;
	}
	int step = 0;
	std::vector<double > ker;
	GaussKernel(ker, sigma, kernelsize);
	if (ker.size() == 0) return;
	cv::Mat kernel;
	kernel.create(Size(kernelsize, kernelsize), CV_64FC1);
	//生成卷积核
	for (int h = 0; h < kernel.rows; h++)
	{
		for (int w = 0; w < kernel.cols; w++)
		{
			kernel.at<double>(h, w) = ker[step++];
		}
	}
	cv::Mat result;
	result.create(src.size(), src.depth());
	//滤波
	double ConSum = 0.f;
	int ker_cen= kernelsize / 2;
	
	for (int i = ker_cen; i < src.rows - ker_cen-1; i++)
	{
		for (int j = ker_cen; j < src.cols - ker_cen-1; j++)
		{
			for (int m = -ker_cen; m < ker_cen; m++)
			{
				for (int n = -ker_cen; n < ker_cen; n++)
				{
					ConSum += static_cast<float>(kernel.at<double>(m+1, n+1)*static_cast<double>(src.at<uchar>(i + m, j + n)));
				}
			}

			
			if (ConSum < 1e-6) ConSum = 0;
			if (ConSum>255) ConSum = 255;
			uchar piexl = static_cast<uchar>(ConSum);
			result.at<uchar>(i, j) = (uchar)(ConSum);
			ConSum = 0;
		}
	}
	if (true)
	{
		imshow("gauss", result);
	}
	src = result.clone();
	result.release();
	kernel.release();
}

#if 1
void LocalMaxValue(cv::Mat &src,cv::Mat &direction)
{
	cv::Mat result;
	result.create(src.size(), src.depth());
	if (!src.data || !direction.data)
	{
		printf("image is null!\n"); 
		return;
	}
	for (int i = 1; i < src.rows-1; i++)
	{
		for (int j = 1; j < src.cols-1; j++)
		{
			float NE = static_cast<float>(src.at<uchar>(i - 1, j - 1));
			float N = static_cast<float>(src.at<uchar>(i - 1, j));
			float NW = static_cast<float>(src.at<uchar>(i - 1, j + 1));
			float  E = static_cast<float>(src.at<uchar>(i, j - 1));
			float M = static_cast<float>(src.at<uchar>(i, j));
			float W = static_cast<float>(src.at<uchar>(i, j + 1));
			float SE = static_cast<float>(src.at<uchar>(i + 1, j - 1));
			float S = static_cast<float>(src.at<uchar>(i + 1, j));
			float SW = static_cast<float>(src.at<uchar>(i + 1, j + 1));
			//0-45  相邻像素之间的距离为1
			float theat = direction.at<float>(i, j);
			float Pro = 1 * tan(theat);//距离系数
			if (direction.at<float>(i, j) > 0 || direction.at<float>(i, j) <= 45)
			{
				float interp1 = NW*Pro + W*(1 - Pro);
				float interp2 = E*(1 - Pro) + SE*Pro;
				if (M < interp1 || M< interp2)
				{
					result.at<uchar>(i, j) = 0;
				}
				else
					result.at<uchar>(i, j) = src.at<uchar>(i, j);
			}
			//45-90
			if (direction.at<float>(i, j) > 0 || direction.at<float>(i, j) <= 45)
			{
				float coe = 1.0f / Pro;
				float interp1 = NW*coe + N*(1 - coe);
				float interp2 = SE*coe + S*(1 - coe);
				if (W < interp1 || M< interp2)
				{
					result.at<uchar>(i, j) = 0;
				}
				else
					result.at<uchar>(i, j) = src.at<uchar>(i, j);

			}
			//-90- -45
			if (direction.at<float>(i, j) > 0 || direction.at<float>(i, j) <= 45)
			{
				float coe = -1.0f / Pro;

				float interp1 = NW*coe + N*(1 - Pro);
				float interp2 = SW*coe + W*(1 - coe);
				if (M < interp1 || M< interp2)
				{
					result.at<uchar>(i, j) = 0;
				}
				else
					result.at<uchar>(i, j) = src.at<uchar>(i, j);
			}
			//-45-0
			if (direction.at<float>(i, j) > 0 || direction.at<float>(i, j) <= 45)
			{
				float coe = -Pro;

				float interp1 = NE*coe + E*(1 - Pro);
				float interp2 = SE*coe + S*(1 - coe);
				if (M < interp1 || M< interp2)
				{
					result.at<uchar>(i, j) = 0;
				}
				else
					result.at<uchar>(i, j) = src.at<uchar>(i, j);
			}

		}
	}
	result.copyTo(src);
}

void LocalMaxValue(const Mat imageInput, Mat &imageOutput, cv::Mat &pointDrection, bool flag = true)
{
	//imageInput.copyTo(imageOutput);
	imageOutput = imageInput.clone();
	int k = 0;
	for (int i = 1; i<imageInput.rows - 1; i++)
	{
		for (int j = 1; j<imageInput.cols - 1; j++)
		{
			int value00 = imageInput.at<uchar>((i - 1), j - 1);
			int value01 = imageInput.at<uchar>((i - 1), j);
			int value02 = imageInput.at<uchar>((i - 1), j + 1);
			int value10 = imageInput.at<uchar>((i), j - 1);
			int value11 = imageInput.at<uchar>((i), j);
			int value12 = imageInput.at<uchar>((i), j + 1);
			int value20 = imageInput.at<uchar>((i + 1), j - 1);
			int value21 = imageInput.at<uchar>((i + 1), j);
			int value22 = imageInput.at<uchar>((i + 1), j + 1);

			if (pointDrection.at<float>(i,j)>0 && pointDrection.at<float>(i,j) <= 45)
			{
				if (value11 <= (value12 + (value02 - value12)*tan(pointDrection.at<float>(i,j))) || (value11 <= (value10 + (value20 - value10)*tan(pointDrection.at<float>(i,j)))))
				{
					imageOutput.at<uchar>(i, j) = 0;
				}
			}
			if (pointDrection.at<float>(i,j)>45 && pointDrection.at<float>(i,j) <= 90)

			{
				if (value11 <= (value01 + (value02 - value01) / tan(pointDrection.at<float>(i,j))) || value11 <= (value21 + (value20 - value21) / tan(pointDrection.at<float>(i,j))))
				{
					imageOutput.at<uchar>(i, j) = 0;

				}
			}
			if (pointDrection.at<float>(i,j)>90 && pointDrection.at<float>(i,j)<= 135)
			{
				if (value11 <= (value01 + (value00 - value01) / tan(180 - pointDrection.at<float>(i,j))) || value11 <= (value21 + (value22 - value21) / tan(180 - pointDrection.at<float>(i,j))))
				{
					imageOutput.at<uchar>(i, j) = 0;
				}
			}
			if (pointDrection.at<float>(i,j)>135 && pointDrection.at<float>(i,j) <= 180)
			{
				if (value11 <= (value10 + (value00 - value10)*tan(180 - pointDrection.at<float>(i,j))) || value11 <= (value12 + (value22 - value11)*tan(180 - pointDrection.at<float>(i,j))))
				{
					imageOutput.at<uchar>(i, j) = 0;
				}
			}
			k++;
		}
	}
}


#endif

void doublethreshold(cv::Mat &src, int lowthres, int hightthres)
{
	if (!src.data)
	{
		printf("image data is null!\n");
		return;
	}
	//cv::Mat result = cv::Mat(src.size(), CV_8UC1);
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			if (src.at<uchar>(i, j) >= hightthres&& src.at<uchar>(i, j) <= 255)
				src.at<uchar>(i, j) = 255;
			if (src.at<uchar>(i, j) < lowthres)
				src.at<uchar>(i, j) = 0;
		}
}

}
#define DEBUG 0
//计算梯度幅值和方向
void GradAmplitude(cv::Mat &src, cv::Mat &gradAmp,cv::Mat &graddirec)
{
	cv::Mat kerobely = (Mat_<char>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
	cv::Mat kerobelx = (Mat_<char>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
	cv::Mat HgradMat, VgradMat;
	HgradMat.create(src.size(), CV_8UC1);
	VgradMat.create(src.size(), CV_8UC1);
	cv::Mat gradmat,dircetmat;
	int center = 3/2;
	int  sobelx, sobely;
	for (int i = center; i < src.rows - center; i++)
	{
		for (int j = center; j < src.cols - center; j++)
		{
			sobelx = sobely = 0;
			for (int m = 0; m < 3; m++)
			{
				for (int n = 0; n < 3; n++)
				{
					sobelx += static_cast<int>((kerobelx.at<char>(m , n )*(src.at<uchar>(i + m-1, j + n-1))));
					sobely += static_cast<int>((kerobely.at<char>(m , n )*(src.at<uchar>(i + m-1, j + n-1))));
				}
			}
			if (sobelx < 0) sobelx = 0;
			else if (sobelx>255) sobelx = 255;

			if (sobely < 0) sobely = 0;
			else if (sobely>255) sobely = 255;
			HgradMat.at<uchar>(i, j) = static_cast<int>(sobelx);
			VgradMat.at<uchar>(i, j) = static_cast<int>(sobely);
		}
	}
	if (DEBUG)
	{
		imshow("sobelx", HgradMat);
		imshow("sobely", VgradMat);
		waitKey(0);
		cvDestroyAllWindows();
	}
	double Amplitude=0.f, direction=0.f;
	gradmat.create(HgradMat.size(), CV_32FC1);
	dircetmat.create(src.size(), CV_32FC1);
	//计算梯度赋值和方向
	for (int k = 0; k < HgradMat.rows; ++k)
	{
		for (int n = 0; n < HgradMat.cols; ++n)
		{
			gradmat.at<float>(k, n) = sqrt(HgradMat.at<uchar>(k, n)*HgradMat.at<uchar>(k, n) + VgradMat.at<uchar>(k, n)* VgradMat.at<uchar>(k, n));//梯度
			dircetmat.at<float>(k, n) = atan2f(HgradMat.at<uchar>(k, n), VgradMat.at<uchar>(k, n))*57.3;
		}
	}
	gradAmp = gradmat.clone();
	graddirec = dircetmat.clone();
	convertScaleAbs(gradmat, gradAmp);
	HgradMat.release();
	VgradMat.release();
	gradmat.release();
	dircetmat.release();

}
void DoubleThresholdLink(Mat &imageInput, double lowThreshold, double highThreshold)
{
	for (int i = 1; i<imageInput.rows - 1; i++)
	{
		for (int j = 1; j<imageInput.cols - 1; j++)
		{
			if (imageInput.at<uchar>(i, j)>lowThreshold&&imageInput.at<uchar>(i, j)<255)
			{
				if (imageInput.at<uchar>(i - 1, j - 1) == 255 || imageInput.at<uchar>(i - 1, j) == 255 || imageInput.at<uchar>(i - 1, j + 1) == 255 ||
					imageInput.at<uchar>(i, j - 1) == 255 || imageInput.at<uchar>(i, j) == 255 || imageInput.at<uchar>(i, j + 1) == 255 ||
					imageInput.at<uchar>(i + 1, j - 1) == 255 || imageInput.at<uchar>(i + 1, j) == 255 || imageInput.at<uchar>(i + 1, j + 1) == 255)
				{
					imageInput.at<uchar>(i, j) = 255;
					DoubleThresholdLink(imageInput, lowThreshold, highThreshold); //递归调用
				}
				else
				{
					imageInput.at<uchar>(i, j) = 0;
				}
			}
		}
	}
}

void mycanny(cv::Mat &src, bool x)
{
	cv::Mat gradAmp, graddirection;
	//高斯滤波
	GaussFilter(src, 3, 1.3);
	
	//梯度幅值和方向
	GradAmplitude(src, gradAmp, graddirection);
	//非极大值抑制
	LocalMaxValue(gradAmp, graddirection);
	imshow("gradAmp", gradAmp);

	//双阈值检测和链接边缘
	doublethreshold(gradAmp, 60, 100);
	DoubleThresholdLink(gradAmp,60, 100);

	imshow("doubleres", gradAmp);

	waitKey(0);
}


void mycanny(cv::Mat &src)
{
	//cv::Mat color = cv::Mat(src.size(), CV_8UC3);
	Mat resultImg = src.clone();
	Mat m_resultImg = Mat(resultImg.rows, resultImg.cols, CV_8UC3);
	cvtColor(resultImg, m_resultImg, CV_GRAY2BGR);
	//int len = src.size();
	cv::putText(m_resultImg, "qwed", cv::Point(5, 10), 1, 1.5, cv::Scalar(255, 0, 0));
	
	imshow("m_resultImg", m_resultImg);
	
	
}


////////////////////////////////////////////////////////////////////////////////////////
int main10(int argc, char* argv[])
{
	//cv::Mat image = imread("D:/Work/code/LearnOpencv/OpencvBase/img/0.jpg");
	cv::Mat image = imread("D:/Work/code/LearnOpencv/OpencvBase/img/0.jpg");
	Proceimg img;
	FilterMethod method = medialfilter;

	cv::Mat dest;
	if (!image.data)
		return -1;
	cv::Mat colorgray;
	cvtColor(image, colorgray, CV_BGR2GRAY);
	//img.movePiexl(150, 150, colorgray);
	//img.imgHorMairror(colorgray);
	//img.imgVerMairror(colorgray);
	//img.imgVerMairror(colorgray);
	//MatrixTransposition(colorgray);
	//img.ImageRotate(colorgray, 20.5);
	//img.ImageRotate(colorgray, 20.5,cv::Point(-1,-1));

	//cv::Mat dstimg;
	//cv::Mat sobelh, sobelv;
	//sobelh = sobelv = colorgray;
	//img.ImageFilter(sobelh, 2);
	//imshow("sobelh", sobelh);

	//img.ImageFilter(colorgray, 2);
	//imshow("sobelv", colorgray);
	//cv::Mat grad_x, grad_y;
	//Sobel(colorgray, grad_x, colorgray.depth(), 1, 0, 3, 1, 1, BORDER_DEFAULT);
	//imshow("x方向soble", grad_x);
	////求y方向梯度
	//Sobel(colorgray, grad_y, colorgray.depth(), 0, 1, 3, 1, 1, BORDER_DEFAULT);
	//imshow("y方向soble", grad_y);
	//img.ImageZoom(colorgray, dstimg,1.5);
	//imshow("det", dstimg);
	//img.filter(colorgray, dstimg, method);
	//imshow("dst", dstimg);

	//imshow("main win", colorgray);
    //	cv::Mat dst;
	//EnhanceFilter(image, dst,1.0f);
	imshow("src", image);
	//boderexpand(image);
	//imshow("main win", dst);
	//std::vector<double > ker;
//	GaussKernel(ker,1.2,3);
	mycanny(colorgray,true);
	//GaussFilter(colorgray,3, 1.3);
	imshow("colorgray", colorgray);
	waitKey(0);



}

int main05(int argc, char* argv[])
{
	cv::Mat image = imread("D:/Work/code/LearnOpencv/OpencvBase/img/0.jpg");
	Proceimg img;
	img.getgrayMat(image);
	for (int i = 0; i < image.rows; i+=100){
		for (int j = 0; j < image.cols; j+=100)
		{
			image.at<uchar>(i, j) = 255;
		}
	}
	imshow("./lenasalt.jpg", image);
	imwrite("./lenasalt.jpg", image);
	getchar();
	return 0;
}

class tabA
{
public :
	void set_val(int _x, int _y)
	{
	x = _x;
	y = _y;
	}
	void set_dval(double _dx, double _dy)
	{
		dx = _dx;
		dy = _dy; 
	}
	void disp()
	{
		cout << x << " " << y << " " << dx << " " << dy << endl;
	}
public:
	int x, y;
	double dx, dy;
};
tabA ops_pt;
int main_2()
{
	ops_pt.set_val(2, 0);
	ops_pt.set_dval(3.0, 5.0);
	ops_pt.disp();
	//Sleep(1000);

	getchar();
	return 0;
}



#include <iostream>
#include <opencv.hpp>

using namespace cv;
using namespace std;



int main02(){

	Mat image = imread("D:/Work/code/LearnOpencv/OpencvBase/img/0.jpg", 1);
	//imshow("result",image);
	//waitKey(0);


	GaussianBlur(image, image, cvSize(5, 5), 5, 5);//高斯模糊
	cvtColor(image, image, CV_RGB2GRAY);
	//cout<<image;

	Mat ModelLaplacian(3, 3, CV_8SC1);

	ModelLaplacian.at<char>(0, 0) = 0;
	ModelLaplacian.at<char>(0, 1) = 1;
	ModelLaplacian.at<char>(0, 2) = 0;
	ModelLaplacian.at<char>(1, 0) = 1;
	ModelLaplacian.at<char>(1, 1) = -4;
	ModelLaplacian.at<char>(1, 2) = 1;
	ModelLaplacian.at<char>(2, 0) = 0;
	ModelLaplacian.at<char>(2, 1) = 1;
	ModelLaplacian.at<char>(2, 2) = 0;


	Mat lapimage = Mat(image.rows, image.cols, CV_8UC1);
	for (int i = 1; i<image.rows - 1; i++){
		for (int j = 1; j<image.cols - 1; j++){

			int sum = 0;//加权求和
			for (int m = 0; m<3; m++){
				for (int n = 0; n<3; n++){
					sum += ((int)ModelLaplacian.at<char>(m, n)*(int)image.at<uchar>(i + m - 1, j + n - 1));
				}
			}
			lapimage.at<uchar>(i, j) = sum;

		}
	}

	imshow("result", lapimage);
	waitKey(0);
	system("pause");
	return 0;
}

int main06()
{
	uchar ch = 230;
	float fl= 0.30f;
	float val= ch*fl;
	uchar vach = (uchar)val;
	return 0;
}

int main08(int argc, char* argv[])
{
	//cv::Mat srcimg = imread("C:/Users/YJH/Desktop/on_colorful_0.jpg");
	cv::Mat srcimg = imread("C:/Users/YJH/Desktop/3l.jpg");
	if (!srcimg.data)
	{
		printf("loading Image failed!\n");
		return -1;
	}
	cv::Mat lightcolor;
	std::vector<cv::Mat> hsvSplit;
	hsvSplit.clear();
	cvtColor(srcimg, lightcolor, CV_BGR2HSV);
	split(lightcolor, hsvSplit);
	cv::Scalar light = cv::mean(hsvSplit[2]);
	
	int sum = light[0];
	printf("color:%d", sum);
	return 0;
}

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/gpu/gpu.hpp>

#include <stdio.h>

using namespace cv;
//行人检测
int main09(int argc, char** argv){
	Mat img;
	vector<Rect> found;

	img = imread("D:/原笔记本数据备份/F盘/资料备份/算法学习/图片/persion.jpg");

	/*if (argc != 2 || !img.data){
		printf("没有图片\n");
		return -1;
	}*/
	cout << "step:" << img.step[0] <<" step1:"<< img.step1(0)<<endl;
	HOGDescriptor defaultHog;
	defaultHog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

	//进行检测
	defaultHog.detectMultiScale(img, found);

	//画长方形，框出行人
	for (int i = 0; i < found.size(); i++){
		Rect r = found[i];
		rectangle(img, r.tl(), r.br(), Scalar(0, 0, 255), 3);
	}


	namedWindow("检测行人", CV_WINDOW_AUTOSIZE);
	imshow("检测行人", img);

	waitKey(0);

	return 0;
}
bool ReadCameraClimbPar(const string &parpath)
{
	if (parpath.empty())
	{
		//LOGE("Path is not Available! ");
		return false;
	}
	ifstream par_file(parpath);
	if (!par_file.is_open())
	{
		//LOGD("Open File Failed!");
		return false;
	}
	string str = "";
	int par = 0;
	vector<int> param;
	param.clear();
	stringstream ss;
	ss.clear();
	while (std::getline(par_file, str))
	{
		ss.str(str);
		while (ss >> par)
		{
			param.push_back(par);
		}
	}
	if (param.size() == 0)
	{
		//LOGE("Loading Parameter Failed");
		return false;
	}
	int k = 0;
	int _focus_offsets[2][3] = { { 0 }, { 0 } };
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j, k++)
		{
			_focus_offsets[i][j] = param[k];
		}
	}
	return true;
}
int main12()
{
	ReadCameraClimbPar("D:/testdata/readpar.txt");
	return 0;
}