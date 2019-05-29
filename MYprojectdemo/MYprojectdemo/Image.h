#ifndef __IMAHE_H
#define __IMAGE_H
#include <iostream>
#include <opencv2/opencv.hpp>
using  namespace std;
using namespace cv;
/*常量区*/
class ImageOps{
public:
	ImageOps();
	ImageOps(const char* path);/*图片的读写和检测*/
	bool CheckIfPathNull(const char* string);
	void myImageShow();
	bool ImageChannelsorCodeCheck(Mat imginput, Mat &imgoutput);
	bool GetImage(Mat &imginput);
	void ImageOps::ImgTransform(Mat img, int value, int mode);
	void ImgBGR2GRAY(Mat input,Mat &output);
	void TargetExtraction(Mat imginput, Mat &imgout, int mode);
	void PicSmaple(Mat imginput, Mat  &imgoutput);
	void Linearfilter(Mat imginput, Mat &imgoutput, int module);
	void mysobel(Mat imginput, Mat &imgoutput);
	void myLaplance(Mat imginput, Mat &imgoutput);
	void mycanny(Mat imginput);
	void myHoguhLine(Mat imginput, Mat &imgoutput);
	void myHoguhLine(Mat imginput, Mat &imgoutput, int vt);
	~ImageOps()
	{
		if (C_image != NULL)
			C_image = NULL;
		destroyAllWindows();

	}

public:
	cv::Mat image;
	IplImage *C_image;
	/*int image_width;
	int image_height;*/
};


#endif