#pragma once
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>  
using namespace cv;
using namespace std;
typedef enum _FilterMethod{ blurfilter = 0, adaptgauss, medialfilter }FilterMethod;
class Proceimg
{
public:
	Proceimg(){ ; }
	~Proceimg(){ ; }
	void movePiexl(int x_len, int y_len, cv::Mat& srcimg);
	void imgHorMairror(cv::Mat& srcimg);
	void imgVerMairror(cv::Mat& srcimg);
	void Proceimg::imgVerHorMairror(cv::Mat& srcimg);
	void ImageShow(const std::string picname, const cv::Mat img){ dubugimg = img.clone(); imshow(picname, dubugimg); waitKey(0); }
	bool ImageRotate(cv::Mat& srcimg, const double angle);//图像旋转
	bool ImageRotate(cv::Mat& srcimg, const double angle, cv::Point rotatecen);
	void ImageZoom(cv::Mat &srcimg, cv::Mat &dst, float scale);
	void getgrayMat(cv::Mat &colorimg);
	void ImageFilter(cv::Mat &srcimg, int kerneltype);
	void filter(cv::Mat& src, cv::Mat &dst, FilterMethod method);
	void meanfilter(cv::Mat& src);
	void medialFilter(cv::Mat &src);
	void Proceimg::AdaptFilter(cv::Mat& src);
	void Proceimg::AdvmedialFilter(cv::Mat &src);
	//img_x, img_y 待处理的当前点坐标
	//
	//
	void Proceimg::AdaptmedialFilter(cv::Mat &src, int img_x, int img_y, int kernelsize, int kernelmax, uchar &piexlval);
	/**
	*  Author:LiBin
	*  Description:双线性插值运算
	*  @param  x,y：需要计算插值的坐标
	*  @param  src:待计算插值原图像
	*  @return:插值运算得到灰度值
	**/
	uchar Proceimg::InterBilinear(float x, float y, cv::Mat &src);
	//void operator()(const cv::Mat &img){ ; }
	
private:
	cv::Mat dubugimg;



};