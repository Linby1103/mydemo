#include "tmpmatch.h"
#include <opencv2/opencv.hpp>

/*source*/
using  namespace std;
using namespace cv;
const char* sourceImage = "sourceImage";
Point pre_pt, cur_pt;
Mat ReserchImg,tmpImg;
Rect SquareRect,drawRect;
/*函数声明区*/
void drawing_image();
void Clean();
void Image_fileter(Mat resImg, Mat &output_img);
void matcher(Mat researchImg, Mat tmpImg, Mat DrawImg);
int Img_remap(Mat input, Mat &outout);
void on_mouse(int event, int x, int y, int flags, void *param)
{
	Mat drawImage,remapImage;
	ReserchImg.copyTo(drawImage);
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		pre_pt = cur_pt = Point(-1, -1);
		pre_pt = cur_pt = Point(x, y);
		//if (cur_pt == Point(-1, -1))
		cout << "鼠标按下，当前坐标为:" << cur_pt << endl;
	}
	else if (event == CV_EVENT_MOUSEMOVE&&(flags == CV_EVENT_FLAG_LBUTTON))
	{
		cur_pt = Point(x, y);
	}
	else if (event == CV_EVENT_LBUTTONUP)
	{
		SquareRect = Rect(-1, -1, 1, 1);
		cur_pt = Point(x, y);
		int tmp_height = cur_pt.y - pre_pt.y;
		int tmp_width = cur_pt.x - pre_pt.x;
		SquareRect.x = pre_pt.x;
		SquareRect.y = pre_pt.y;
		SquareRect.width = tmp_width;
		SquareRect.height = tmp_height;
		cout << "鼠标按下之前坐标为:" << cur_pt << endl;

		if (SquareRect.area() >125 || (SquareRect.width >15 && SquareRect.height > 15))
		{
			tmpImg = ReserchImg(SquareRect).clone();
			if (tmpImg.empty())
			{
				return;
			}
		//	Img_remap(tmpImg,remapImage);
			matcher(ReserchImg, tmpImg, drawImage);
		}
	}
}

int main61(int argc, char *argv[])
{
	 ReserchImg = imread("./picdemo/lena.jpg");
	char tim = '0';
	if (!ReserchImg.data)
	{
		cout << "loading image failed" << endl;
		return 0;
	}
	/*鼠标事件*/
	cv::namedWindow("sourceImage", CV_WINDOW_AUTOSIZE);
	cvSetMouseCallback(sourceImage, on_mouse, NULL);
	{
		drawing_image();
		//imshow(sourceImage, ReserchImg);
		waitKey(0);	
	}
	
	return 0;
}
char coord[20] = {'0'};
void drawing_image()
{
	if (SquareRect.area() >125 || (SquareRect.width >15 && SquareRect.height > 15))
	{
		sprintf_s(coord, "(%d ,%d)", SquareRect.x, SquareRect.y);
		putText(ReserchImg, coord, cur_pt, cv::FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 0));
		rectangle(ReserchImg, SquareRect, Scalar(0, 255, 255));
	}

	imshow(sourceImage, ReserchImg);
}
void Clean()
{
	SquareRect.x = -1;
	SquareRect.y = -1;
	SquareRect.width = 0;
	SquareRect.height = 0;
}
void Image_fileter(Mat resImg, Mat &output_img)
{
	Mat _resImg;
	if (resImg.channels() != 1) cvtColor(resImg, _resImg, CV_BGR2GRAY);
	/*均衡化处理*/
	equalizeHist(_resImg, output_img);
	/*高斯滤波*/
	Mat Kernel = getStructuringElement(cv::MORPH_RECT, Size(5, 5), Point(-1, -1));
	GaussianBlur(output_img, output_img, Size(5, 5),0);
	/*求梯度*/
	morphologyEx(output_img, output_img, cv::MORPH_GRADIENT, Kernel);
}
void matcher(Mat researchImg, Mat tmpImg,Mat DrawImg)
{
	Mat Resch_img, tmp_img;
	double min = 0.0, max = 0.0;
	Point  minLoc = Point(-1, -1), maxLoc = Point(-1, -1);
	int tmp_w = researchImg.cols - tmpImg.cols+1;
	int tmp_h = researchImg.rows - tmpImg.rows + 1;
	Mat mat_mval = Mat(Size(tmp_w, tmp_h), CV_32FC1);
	Image_fileter(researchImg, Resch_img);
	Image_fileter(tmpImg, tmp_img);
	matchTemplate(Resch_img, tmp_img, mat_mval, TM_CCOEFF_NORMED);
	//normalize(mat_mval, mat_mval, 0, 1);
	char mat_ch[50] = {0};
	minMaxLoc(mat_mval, &min, &max, &minLoc,&maxLoc,Mat());
	drawRect = Rect(maxLoc, Size(tmpImg.cols, tmpImg.rows));
	sprintf_s(mat_ch, "good match(%.1f)", max);
	putText(DrawImg, mat_ch, drawRect.br(), cv::FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));
	rectangle(DrawImg, drawRect, Scalar(255, 0, 0));
	imshow("match", DrawImg);
}
/*图片的放射变化*/
int Img_remap(Mat input ,Mat &outout)
{
	Mat image, imgx, imgy, remapdst;
	char mode = '0';
	image = input.clone();
	if (image.empty())
	{
		cout << "Picture load error" << endl;
		return -1;
	}
	imgx.create(image.size(), CV_32FC1);
	imgy.create(image.size(), CV_32FC1);
	
		for (int row = 0; row < image.rows; ++row)
		{
			for (int col = 0; col < image.cols; ++col)
			{
					imgx.at<float>(row, col) = saturate_cast<float>(image.rows - row);
					imgy.at<float>(row, col) = saturate_cast<float>(image.cols - col);
			}
		}
		remap(image, remapdst, imgx, imgy, INTER_LINEAR);
		remapdst.copyTo(outout);
		imshow("remap", remapdst);
	}



void sampleClass::printf_val()
{
	std::cout << "\tvc= " << vc << "\t va= " << va << " \tvb " << vb << std::endl; 
	std::cout << "this address:\t " << this << std::endl;
}
void sampleClass::SetVal(int va_, int vb_)
{ 
	
	//pThis2->va = va_;
	//pThis2->vb = vb_;
	//pThis2->vc = va + vb;
	//pThis2->vc = pThis2->va + pThis2->vb;
	sampleClass valsoop;
	va = va_;
	vb = vb_;
	vc = va + vb;
	vc = va + vb;
	setTemp(valsoop);

	std::cout << "this function:\tvc= " << vc << "\t va= " << va << " \tvb " << vb << std::endl;
	//std::cout << "this address:\t " <<this << std::endl;
	//std::cout << "pThis2 address:\t " << pThis2 << std::endl;
	printf_val();
}
void sampleClass::setTemp(sampleClass& class1)
{
	//class1.SetVal(1, 8);
	class1.printf_val();
}

void sampleClass::SetVecVal()
{
	for (int i = 0; i < 3; i++)
	{
		pthis1.push_back(sampleClass());
		sampleClass &pt = pthis1.back();
		//pthis1.reserve(5);
		pt.sampleClassrest();
		pt.SetVal(i, i + 1); 
		pt.printf_val();
	}
	

}
void sampleClass::sampleClassrest()
{
	pthis1.push_back(sampleClass());
	sampleClass* mainpThis2 = &pthis1[0];
	mainpThis2->SetVal(10, 10);
	mainpThis2->printf_val();
	cout << "mainThis  " << mainpThis2 << endl;
	//va = vb = vc = 0;
}
int main71(int argc,char *argv[])
{
	sampleClass classp;
	classp.sampleClassrest();
	std::cout << "classp address:\t " << &classp << std::endl;
	return 0;
}