#include <iostream>
#include <cstring>
#include "Image.h"
using namespace std;
using namespace cv;
const String win = "mainwindow";
int main01()
{
	Mat img = imread("./picdemo/lena.jpg");
	Mat img_cpy = imread("./picdemo/lena.jpg");
	Mat imgdst;
	if (img.empty()||!img_cpy.data)
	{
		cout << "not found image" << endl;
		return -1;
	}
	addWeighted(img, 0.5, img_cpy, 0.5, 0.0, imgdst);
	namedWindow(win, WINDOW_AUTOSIZE);
	imshow(win, imgdst);
	cout << "img="<<img.channels()<< endl;
	waitKey(0);
	return 1;
}
Mat contrastRratio(const Mat img)
{
	int col, row;
	double alpha = 1.2, beta = 30;
	Mat dstMat = Mat::zeros(img.size(), img.type());
	for (row = 0; row < img.rows;row++)
	for (col = 0; col < img.cols; col++)
	{
		if (img.channels() == 3)
		{
			uchar b = img.at<Vec3b>(row, col)[0];
			uchar g = img.at<Vec3b>(row, col)[1];
			uchar r = img.at<Vec3b>(row, col)[2];
			dstMat.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b*alpha + beta);
			dstMat.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g*alpha + beta);
			dstMat.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r*alpha + beta);
		}
		else
		{
			float v = img.at<uchar>(row, col);
			dstMat.at<uchar>(row,col) = saturate_cast<uchar>(v + alpha + beta);

		}
	}
	return dstMat;

}
int main02()
{
	
	Mat img = imread("./picdemo/lena.jpg");
	Mat imgdst;
	if (img.empty())
	{
		cout << "not found image" << endl;
		return -1;
	}
	imgdst = contrastRratio(img);
	imshow("src", img);
	namedWindow(win, WINDOW_AUTOSIZE);
	imshow(win, imgdst);
	cout << "img=" << img.channels() << endl;
	double value = 5.678;
	int recvaldow = std::floor(value);
	int recvalup = std::ceil(value);
	cout << "向下取整：" << recvaldow << "  向上取整 " << recvalup << endl;
	waitKey(0);
	return 1;
}
/*随机数*/
int main03()
{
	RNG radomRNG(12345);
	Point pt1, pt2;
	Mat img = Mat::zeros(Size(1920, 1080), CV_8UC3);
	for (int id = 0; id < 5000; ++id)
	{
		pt1.x = radomRNG.uniform(0, img.cols);
		pt2.x = radomRNG.uniform(0, img.cols);
		pt1.y = radomRNG.uniform(0, img.rows);
		pt1.y = radomRNG.uniform(0, img.rows);
		Scalar color(radomRNG.uniform(0, 255), radomRNG.uniform(0, 255), radomRNG.uniform(0, 255));

		if (waitKey(50)>0)
		{
			break;
		}
		line(img, pt1, pt2, color, 1.5, 8);
		imshow("drawline", img);
	}


	return  0;
}
/*模糊*/
int  main04()
{
	Mat src, dst;
	src = imread("./picdemo/lena.jpg");
	if (!src.data)
	{
		cout << "read image error" << endl;
		return -1;
	}
	imshow("src", src);
	/*中值模糊*/
	blur(src, dst, Size(11, 11), Point(-1, -1));
	imshow("中值", dst);
	/*高斯模糊*/
	GaussianBlur(src, dst, Size(11, 11),11,11);
	imshow("高斯模糊", dst);
	waitKey(0);
	return 0;
}
/*高斯滤波和双边滤波*/
int mainbnm()
{
	Mat imgsrc = imread("./picdemo/lena.jpg");
	Mat gaussdst;
	if (imgsrc.empty())
	{
		cout << "read image error" << endl;
		return -1;
	}
	imshow("src", imgsrc);
	GaussianBlur(imgsrc, gaussdst, Size(11, 11), 2.0, 3.0);     
	imshow("gaussianBlur", gaussdst);
	waitKey(0);
	return 0;
}
int *returntmp(int a,int b)
{
	int c = a + b;
	return &c;
}
int main10()
{
	int *tmp=NULL;
	tmp = returntmp(2,3);
	cout << "printf tmp :" << *tmp << endl;
	int *ttmp = returntmp(2, 3);
	cout << "printf ttmp :" << *ttmp << endl;
	while (1);
	return 1;
}
class returntmpt{
public:
	int &returntmptint(int _a)
	{
		int a = _a * 5;
		return a;
	}

	char &returntmptchar(char ch)
	{
		char b = ch + 10;
		return b;
	
	}
	string &returntmpstring(string _ss)
	{
		
		string ss = _ss;
		return ss;

	}


	
};
int main05()
{
	string sts = "hello";
	returntmpt tmp;
	{
		int tmp_int = tmp.returntmptint(3);
		cout << "return int value:" << tmp_int << endl;
		char ch = tmp.returntmptchar('a');
		cout << "return char value:" << ch << endl;
		//string ss_ = tmp.returntmpstring(sts);
		//cout << "return string value:" << ss_ << endl;
	}
	system("pause");

	return 0;
}
/*分段线性变换*/

void  ParLinTran(Mat imginput,Mat &imgoutput,int x1,int y1,int x2,int y2)
{
	static int count = 0;
	Mat retimg = Mat::zeros(imginput.size(), imginput.depth());
	
	/*防止异常输入*/
	if (x1 == x2||x1==0||x2==255)
	{
		if (x1 == x2)
			throw (x1 - x2);
		if (x1 == 0)
			throw 1;
		if (x2 == 255)
			throw 255;
	}
	for (int rows = 0; rows < imginput.rows; rows++)
	{
		for (int cols = 0; cols < imginput.cols; cols++)
		{
			//count++;
			//cout << count<<"<-step\t" ;
			uchar gray = imginput.at<uchar>(rows, cols);
			if (gray < x1)
			{
				retimg.at<uchar>(rows, cols) = saturate_cast<uchar>(gray*y1 / x1);
			}
			else if (gray >= x1&&gray <= x2)
			{
				retimg.at<uchar>(rows, cols) = saturate_cast<uchar>((gray - x1)*(y2 - y1) / (x2 - x1) + y1);
			}
			else
			{
				retimg.at<uchar>(rows, cols) = saturate_cast<uchar>((gray -x2)*(255 - y2) / (255 - x2) + y2);
			}
		}
	
	}
	
	retimg.copyTo(imgoutput);
}
void ChangeGrayVal(int);
Point pt1, pt2;
Mat dst;
Mat imgsrc;
int x1point=50, y1point=90, x2point=230, y2point=215;
int counts = 255;
int main07()
{
	Mat tmpimg;
	imgsrc = imread("./picdemo/lena.jpg");
	namedWindow("imagesrc", WINDOW_AUTOSIZE);
	namedWindow("imagedst", WINDOW_AUTOSIZE);
	
	if (imgsrc.empty())
	{
		cout << "read image error" << endl;
		return -1;
	}
	int channls = imgsrc.channels();
	if (channls == 3)
	{
		cvtColor(imgsrc, tmpimg, CV_BGR2GRAY);
		//imginput=tmpimg.clone();
		//tmpimg.copyTo(imginput);
	}

	imshow("imagesrc", tmpimg);
	
# if 1
	try{
		/*创建滑动条*/
		
		cvCreateTrackbar("tarckbar1", "imagedst", &x1point, counts, ChangeGrayVal);
		cvCreateTrackbar("tarckbar2", "imagedst", &y1point, counts, ChangeGrayVal);
		cvCreateTrackbar("tarckbar3", "imagedst", &x2point, counts, ChangeGrayVal);
		cvCreateTrackbar("tarckbar4", "imagedst", &y2point, counts, ChangeGrayVal);
		//ParLinTran(tmpimg, dst, 50, 90, 230, 215);
		ChangeGrayVal(0);
		imshow("imagedst", dst);
		if (waitKey(0) == 27)
			return 1;
		
	}
	catch (int eventflg)
	{
		cout << "坐标输入异常" << endl;
	}
#endif
	return 1;
}
void ChangeGrayVal(int)
{
	pt1.x = x1point;
	pt1.y = y1point;
	pt2.x = x2point;
	pt2.y = y2point;
	ParLinTran(imgsrc, dst, x1point, y1point, x2point, y2point);

}
/*opencv图像的开运算*/
int main16()
{
	Mat imgsrc,dst;

	ImageOps Imagedemo("./picdemo/houghlinespic.png");
	Imagedemo.myImageShow();
	Imagedemo.GetImage(imgsrc);
	/*图像运算*/
	//Imagedemo.ImgTransform(imgsrc,7,5);
	//Imagedemo.TargetExtraction(imgsrc, dst, 0);
	//Imagedemo.PicSmaple(imgsrc, dst);
	//Imagedemo.Linearfilter(imgsrc, dst, 3);
	///Imagedemo.mysobel(imgsrc, dst);
	//Imagedemo.myLaplance(imgsrc, dst);

	Imagedemo.myHoguhLine(imgsrc, dst);
	waitKey(0);
	return 1;
}
int main09(int argc,char *argv[])
{
	Mat image = imread("./picdemo/lena.jpg");
	Mat dst;
	if (!image.data)
	{
		cout << "load image error" << endl;
		return -1;
	}
	imshow("src", image);
	int top, botton,left,right;
	top = botton = (int)(0.05*image.rows);
	left = right = (int)(0.05*image.cols);
	RNG rng(12345);
	int borderType = BORDER_DEFAULT;
	char c = '0';
	while (true)
	{
		c = waitKey(500);
		if (c == 27)
			break;
		if (c == 'r')
		{
			borderType = BORDER_REPLICATE;

		}
		else if (c == 'v')   
		{
			borderType = BORDER_WRAP;
		}
		else if (c == 'c')
			borderType = BORDER_CONSTANT;
		else
			borderType = BORDER_DEFAULT;
		Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		copyMakeBorder(image, dst, top, botton, left, right, borderType, color);
		imshow("borderType", dst);
		waitKey(0);
	}
	return 0;
}
int thres1 = 30;
int thresmax = 255;
Mat gaussdst;
//String namewin = "mainwin";
void changeValue(int, void*);
int main12(int argc, char *argv[])
{
	Mat imgsrc = imread("./picdemo/lena.jpg");
	Mat cvtdst;
	namedWindow("mainwin", WINDOW_AUTOSIZE);
	if (imgsrc.empty())
	{
		cout << "load image error" << endl;
		return -1;
	}
	cvtColor(imgsrc, cvtdst, CV_BGR2GRAY);
	/*滤波*/
	GaussianBlur(cvtdst, gaussdst, Size(3, 3), 0, 0);
	cvCreateTrackbar("value", "mainwin", &thres1, thresmax);
	/*边缘提取*/
	changeValue(0,NULL);
	if (waitKey(0) == 27)
		return  1;
	return 0;
}
void changeValue(int ,void*)
{
	Mat  edgesdst;
	Canny(gaussdst, edgesdst, thres1, thres1*2,3,false);
	imshow("mainwin", ~edgesdst);

}
/*


*/
int main14(int argc, char** argv)
{
	Mat src, edge, color_edge;
	src = imread("./picdemo/houghlinespic.png");
	if (!src.data)
		return -1;

	Canny(src, edge, 50, 200, 3);
	cvtColor(edge, color_edge, CV_GRAY2BGR);
	vector<Vec4i> lines;
	HoughLinesP(edge, lines, 1, CV_PI / 180, 80, 30, 10);
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(color_edge, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2);
	}

	namedWindow("lines", CV_WINDOW_AUTOSIZE);
	imshow("lines", color_edge);
	waitKey(0);

	return 0;
}

int main60(int argc, char **argv)
{
	Mat image, imgx, imgy,remapdst;
	char mode = '0';
	image = imread("./picdemo/lena.jpg");
	if (image.empty())
	{
		cout << "Picture load error" << endl;
		return -1;
	}
	imshow("src", image);
	imgx.create(image.size(), CV_32FC1);
	imgy.create(image.size(), CV_32FC1);
	while (true)
	{
		for (int row = 0; row < image.rows; ++row)
		{
			for (int col = 0; col < image.cols; ++col)
			{
				if (mode == 0)
				{
					imgx.at<float>(row, col) = saturate_cast<float>(image.rows - row);
					imgy.at<float>(row, col) = saturate_cast<float>(image.cols - col);
				}
				else if (mode == 1)
				{
					/*上下*/
					imgx.at<float>(row, col) =row;
					imgy.at<float>(row, col) = saturate_cast<float>(image.cols - col);
				}
				else if (mode == 2)
				{
					imgx.at<float>(row, col) = saturate_cast<float>(image.rows - row);
					imgy.at<float>(row, col) = col;
				}
				/*if (col>image.cols*0.25&&col<image.cols*0.75&& row > image.rows*0.25&&row < image.rows*0.75)
				{
				imgx.at<float>(row, col) = 2 * saturate_cast<float>(row - image.rows*0.25 + 0.5);
				imgy.at<float>(row, col) = saturate_cast<float>(col - image.cols*0.25 + 0.5);
				}
				else{

				imgx.at<float>(row, col) = 0;
				imgy.at<float>(row, col) = 0;
				}*/
			}
		}
		
		remap(image, remapdst, imgx, imgy, INTER_LINEAR);
		imshow("remap", remapdst);
		imwrite("./mirror.jpg", remapdst);
		mode = waitKey(50);
		if (mode == 27)
			break;                                         
		switch (mode)
		{
		case 72:
			//上
			mode = 1;
			break;
		case 80:
			//下 
			mode = 2;
			break;
		case 75:
			//左
			mode = 3;
			break;
		case 77:
			//右
			mode = 4;
			break;
		default:
			mode = 2;
			break;


		}
	}
	
	return 0;
}