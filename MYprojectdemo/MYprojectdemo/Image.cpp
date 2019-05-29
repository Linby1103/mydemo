#include "Image.h"
string mainwindows = "mainwindows";
#define debug   1
ImageOps::ImageOps(const char* path)
{
	IplImage tmpmat;
	if (CheckIfPathNull(path))
	{
		this->image = imread(path);
		if (image.empty())
		{
			cout << "load image error" << endl;
			return ;
		}

	}
	if (this->C_image != NULL)
	{
		this->C_image = NULL;
	}
	tmpmat = IplImage(image);
	C_image = &(tmpmat);
	if (C_image = NULL)
	{
		cout << "image Transformated failure" << endl;
		return ;
	}
}
bool ImageOps::CheckIfPathNull(const char* string)
{
	if (string == NULL || string[0] == ' ' || strlen(string) < 3)
	{
		std::cout << "path is error" << std::endl;
		return 0;

	}
	else
		return 1;

}
/*图片显示*/
void ImageOps::myImageShow()
{
	imshow(mainwindows, image);
	/*waitKey(0);*/
}
ImageOps::ImageOps()
{

	;
}
bool ImageOps::GetImage(Mat &imginput)
{
	
	this->image.copyTo(imginput);
	if (imginput.data)
	{
		if (this->image.type() == imginput.type() && this->image.depth() == imginput.depth())
			return true;
	}
	return false;
}
void ImageOps::ImgBGR2GRAY(Mat input, Mat &output)
{
	cvtColor(input, output, CV_BGR2GRAY);
}
/*图像形态学运算*/
void ImageOps::ImgTransform(Mat img,int value,int mode)
{
	/*图像开运算*/
	Mat imgrec, open_opsimage, close_opsimage, Gradientimage,tophatimage,blackhatimage,dilateImage,erodeImage;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(value, value), Point(-1, -1));
	ImgBGR2GRAY(img, imgrec);
	switch (mode)
	{
	case 1:
		morphologyEx(imgrec, open_opsimage, MORPH_OPEN, kernel, Point(-1, -1), 1);
		imshow("morph_open", open_opsimage);
		break;
	case 2:
		morphologyEx(imgrec, close_opsimage, MORPH_CLOSE, kernel, Point(-1, -1), 1);
		imshow("morph_close", close_opsimage);
		break;
	case 3:/*形态学梯度*/
		morphologyEx(imgrec, Gradientimage, MORPH_GRADIENT, kernel, Point(-1, -1), 1);
		imshow("tophatimage", Gradientimage);
		break;
	case   4:
	morphologyEx(imgrec, tophatimage, MORPH_TOPHAT, kernel, Point(-1, -1),1);
	imshow("tophatimage", tophatimage);
	break;

	case 5:
		morphologyEx(imgrec, blackhatimage, MORPH_BLACKHAT, kernel, Point(-1, -1), 1);
		imshow("blackhatimage", blackhatimage);
		break;
	case 6:
		dilate(imgrec, dilateImage, kernel, Point(-1, -1));
		imshow("dilateImage", dilateImage);
		break;
	case 7:
		erode(imgrec, erodeImage, kernel, Point(-1, -1));
		imshow("erodeImage", erodeImage);
		break;
	}
	
}
/*水平/垂直目标提取*/
void ImageOps::TargetExtraction(Mat imginput, Mat &imgout,int mode)
{
	Mat  img_Gray,BinImage,dst;
	this->ImgBGR2GRAY(imginput, img_Gray);
	adaptiveThreshold(~img_Gray, BinImage, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, -1);
	/*定义水平结构*/
	Mat kernel_h = getStructuringElement(MORPH_RECT, Size(10, 1), Point(-1, -1));
	/*定义竖直结构*/
	Mat kernel_v = getStructuringElement(MORPH_RECT, Size(1, 7), Point(-1, -1));
	morphologyEx(BinImage, dst, MORPH_OPEN, kernel_v, Point(-1, -1));
	bitwise_not(dst, dst);
	imshow("TargetExtraction", dst);
}
/*图片的上/降采样*/
void ImageOps::PicSmaple(Mat imginput, Mat  &imgoutput)//imgoutput未使用
{
	Mat img_Gray,pyrUPdst,pryDOWNdst;
	Mat imggassFir, imggassSec,SubImg,dogImag;
	if (imginput.channels() != 1)
	{
		this->ImgBGR2GRAY(imginput, img_Gray);
	}
	else
	{
		imginput.copyTo(img_Gray);
	}
	/*上采样*/
	pyrUp(img_Gray, pyrUPdst, Size(img_Gray.cols * 2, img_Gray.rows * 2));
#ifdef debug
	imshow("pyrUp",pyrUPdst);
#endif
	/*降采样*/
	pyrDown(img_Gray, pryDOWNdst, Size(img_Gray.cols / 2, img_Gray.rows / 2));
#ifdef debug
	imshow("pyrDown", pryDOWNdst);
#endif
	/*高斯不同*/
	GaussianBlur(img_Gray, imggassFir, Size(3,3), 0, 0);
	GaussianBlur(imggassFir, imggassSec, Size(3,3), 0, 0);
	subtract(imggassFir, imggassSec, SubImg, Mat());
	/*归一化处理*/
	normalize(SubImg, dogImag, 255, 0, NORM_MINMAX);
#ifdef debug
	imshow("高斯不同", dogImag);
#endif

}

void ImageOps::Linearfilter(Mat imginput, Mat &imgoutput, int mode)
{
	Mat img_Gray, robertfilterdstx, robertfilterdsty, sobelfilterdstx, sobelfilterdsty, LPSfilterdst;
	Mat Robertkernel_x = (Mat_<int>(2, 2) << 1, 0, 0, -1);
	Mat Robertkernel_y = (Mat_<int>(2, 2) << 0, 1, -1, 0);
	Mat sobelkernel_x = (Mat_<int>(3, 3) << -1, 0, 1, -2, -0, 2, -1, -0, 1);
	Mat sobelkernel_y = (Mat_<int>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
	Mat LPSkernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
	if (imginput.channels() != 1)
	{
		this->ImgBGR2GRAY(imginput, img_Gray);
	}
	else
	{
		imginput.copyTo(img_Gray);
	}
	switch (mode)
	{
	case 1:
		filter2D(img_Gray, robertfilterdstx, -1, Robertkernel_x, Point(-1, -1));
		imshow("robertfilterdstx", robertfilterdstx);
		filter2D(img_Gray, robertfilterdsty, -1, Robertkernel_y, Point(-1, -1));
		imshow("filterdsty", robertfilterdsty);
		break;
	case 2:
		filter2D(img_Gray, sobelfilterdstx, -1, sobelkernel_x, Point(-1, -1));
		imshow("sobelfilterdstx", sobelfilterdstx);
		filter2D(img_Gray, sobelfilterdsty, -1, sobelkernel_y, Point(-1, -1));
		imshow("sobelfilterdsty", sobelfilterdsty);
		break;
	case 3:
		filter2D(img_Gray, LPSfilterdst, -1, LPSkernel, Point(-1, -1));
		imshow("LPSfilterdst", LPSfilterdst);
	default :
		return;

	}


}
/*sobel算子*/
void ImageOps::mysobel(Mat imginput, Mat &imgoutput)
{
	Mat img_Gray,imgGassdst,sobelx,sobely;
	if (imginput.channels() != 1)
	{
		this->ImgBGR2GRAY(imginput, img_Gray);
	}
	else
	{
		imginput.copyTo(img_Gray);
	}
	/*对图像滤波*/
	GaussianBlur(img_Gray, imgGassdst, Size(5, 5), 0, 0, BORDER_DEFAULT);
	/*sobelx方向梯度*/
	sobelx = Mat(imgGassdst.size(), imgGassdst.depth());
	sobely = Mat(imgGassdst.size(), imgGassdst.depth());
	Mat sobelxy = Mat(imgGassdst.size(), imgGassdst.depth());
	//Sobel(imgGassdst, sobelx, imgGassdst.depth(), 1, 0);
	Scharr(imgGassdst, sobelx, imgGassdst.depth(), 1, 0);
	imshow("sobelx", sobelx);
	//Sobel(imgGassdst, sobely, imgGassdst.depth(), 0, 1);
	Scharr(imgGassdst, sobely, imgGassdst.depth(), 1, 0);
	imshow("sobely", sobely);
	/*xy合成方向梯度*/
	for (int row = 0; row<imgGassdst.rows; ++row)
	{
		for (int col = 0; col < imgGassdst.cols; ++col)
		{
			uchar pixelx = sobelx.at<uchar>(row, col);
			uchar pixely = sobely.at<uchar>(row, col);
			sobelxy.at<uchar>(row, col) = saturate_cast<uchar>(pixelx + pixely);
		}
	}
	normalize(sobelxy, sobelxy, 0, 255, NORM_MINMAX);
	sobelxy.copyTo(imgoutput);
	imshow("imgoutput", imgoutput);

	imgoutput = sobelxy.clone();
	sobelxy = img_Gray.clone();
	/*imshow("imgoutput", imgoutput);
	imshow("sobelxy", sobelxy);*/

}
void ImageOps::myLaplance(Mat imginput, Mat &imgoutput)
{
	Mat img_Gray, imgGassdst, Laplancetmp, Laplancedst;
	if (imginput.channels() != 1)
	{
		this->ImgBGR2GRAY(imginput, img_Gray);
	}
	else
	{
		imginput.copyTo(img_Gray);
	}
	GaussianBlur(img_Gray, imgGassdst, Size(3, 3), 0, 0);
	Laplacian(imgGassdst, Laplancetmp, CV_16S,3);
	convertScaleAbs(Laplancetmp, Laplancedst);
	threshold(Laplancedst, Laplancedst, 0, 255, THRESH_OTSU | THRESH_BINARY);
	imshow("Laplance", Laplancedst);
}
bool ImageOps::ImageChannelsorCodeCheck(Mat imginput, Mat &imgoutput)
{
	Mat img_Gray;
	bool channelsflag;
	if (imginput.channels() != 1)
	{
	this->ImgBGR2GRAY(imginput, img_Gray);
	channelsflag = false;
	}
	else
	{
	imginput.copyTo(img_Gray);

	channelsflag = true;
	}
	img_Gray.copyTo(imgoutput);
	return channelsflag;
}
void ImageOps::mycanny(Mat imginput)
{
	/*Mat img_Gray, imgGassdst,edgesdst;
	if (imginput.channels() != 1)
	{
		this->ImgBGR2GRAY(imginput, img_Gray);
	}
	else
	{
		imginput.copyTo(img_Gray);
	}
	GaussianBlur(img_Gray, imgGassdst, Size(3, 3),0,0);
	Canny(imgGassdst, edgesdst, thresval, 255);*/

}
/*houghlinespic*/
void ImageOps::myHoguhLine(Mat imginput, Mat &imgoutput)
{
	Mat imgGray,imgBlur,cannydst,imghough,dst;
	ImageChannelsorCodeCheck(imginput, imgGray);
	//imghough = Mat::zeros(imginput.size(), imginput.depth());
	/*滤波*/
	blur(imgGray, imgBlur, Size(3, 3));
	Canny(imgBlur, cannydst, 125, 210);
	cvtColor(cannydst, dst, CV_GRAY2BGR);
	imshow("canny", imgBlur);
	/*霍夫直线检测*/
	vector<Vec4i> houghlinept ;
	HoughLinesP(cannydst, houghlinept, 1, CV_PI / 180.0, 50, 50, 10);
	//HoughLinesP()
	for (int num = 0; num < houghlinept.size(); num++)
	{
		line(dst, Point(houghlinept[num][0], houghlinept[num][1]), Point(houghlinept[num][02], houghlinept[num][3]), Scalar(255 * 0.1, 255 * 0.6, 255 * 0.3), 1);
	}
	imshow("imghough", dst);
	dst.copyTo(imgoutput);
}
void ImageOps::myHoguhLine(Mat imginput, Mat &imgoutput,int vt)
{
	Mat imgGray, imgBlur, imghough, dst, imgBlurdst;
	//ImageChannelsorCodeCheck(imginput, imgGray);
	imghough = Mat::zeros(imginput.size(), imginput.depth());
	/*滤波*/
	blur(imginput, imgBlur, Size(3, 3));
	Canny(imgBlur, imgBlurdst, 125, 210);
	//cvtColor(imgBlurdst, dst, CV_GRAY2BGR);
	imshow("canny", imgBlur);
	/*霍夫直线检测*/
	vector<Vec4i> houghlinept ;
	HoughLinesP(imgBlurdst, houghlinept, 1, CV_PI / 180.0, 50, 50, 10);
	//HoughLinesP()
	for (int num = 0; num < houghlinept.size(); num++)
	{
		line(imghough, Point(houghlinept[num][0], houghlinept[num][1]), Point(houghlinept[num][02], houghlinept[num][3]), Scalar(255	, 255 * 0.6, 255 * 0.3), 1);
	}
	imshow("imghough", imghough);
	imghough.copyTo(imgoutput);
}
