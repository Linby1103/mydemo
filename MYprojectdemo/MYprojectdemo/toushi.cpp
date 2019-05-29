#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <iostream>  
#include <cv.h>
using namespace std;
using namespace cv;


Point2f center(0, 0);

Point2f computeIntersect(Vec4i a, Vec4i b)
{
	int x1 = a[0], y1 = a[1], x2 = a[2], y2 = a[3], x3 = b[0], y3 = b[1], x4 = b[2], y4 = b[3];
	// float denom;  

	if (float d = ((float)(x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4))) 		//若d=0，则直线AB与CD平行或重合
	{
		Point2f pt;
		pt.x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / d;  //求两条直线的交点x坐标
		pt.y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / d;  //求两条直线的交点x坐标
		return pt;
	}
	else
		return Point2f(-1, -1);
}

void sortCorners(std::vector<Point2f>& corners, Point2f center)
{
	vector<Point2f> top, bot;

	for (int i = 0; i < corners.size(); i++)
	{
		if (corners[i].y < center.y)
			top.push_back(corners[i]);
		else
			bot.push_back(corners[i]);
	}
	corners.clear();

	if (top.size() == 2 && bot.size() == 2){
		Point2f tl = top[0].x > top[1].x ? top[1] : top[0];
		Point2f tr = top[0].x > top[1].x ? top[0] : top[1];
		Point2f bl = bot[0].x > bot[1].x ? bot[1] : bot[0];
		Point2f br = bot[0].x > bot[1].x ? bot[0] : bot[1];
		corners.push_back(tl);
		corners.push_back(tr);
		corners.push_back(br);
		corners.push_back(bl);
	}
}

int main80()
{
	Mat srcImage = imread("./picdemo/lena.jpg");//原图  
	if (srcImage.empty())
		return -1;
	Mat grayImage;  				  //灰度图
	cvtColor(srcImage, grayImage, CV_BGR2GRAY); //转化为灰度图 
	blur(grayImage, grayImage, Size(3, 3));   //滤波
	Canny(grayImage, grayImage, 100, 100, 3);

	vector<Vec4i> lines;                    //直线输出向量 
	HoughLinesP(grayImage, lines, 1, CV_PI / 180, 70, 30, 10);  //霍夫直线检测

	// 延伸直线  
	for (int i = 0; i < lines.size(); i++)
	{
		Vec4i v = lines[i];
		lines[i][0] = 0;
		lines[i][1] = ((float)v[1] - v[3]) / (v[0] - v[2]) * -v[0] + v[1];
		lines[i][2] = srcImage.cols;
		lines[i][3] = ((float)v[1] - v[3]) / (v[0] - v[2]) * (srcImage.cols - v[2]) + v[3];
	}

	vector<Point2f> corners;
	for (int i = 0; i < lines.size(); i++)
	{
		for (int j = i + 1; j < lines.size(); j++)
		{
			Point2f pt = computeIntersect(lines[i], lines[j]);//调用自定义函数求相交直线的交点
			if (pt.x >= 0 && pt.y >= 0)
				corners.push_back(pt);
		}
	}

	vector<Point2f> approx;
	approxPolyDP(Mat(corners), approx, arcLength(Mat(corners), true) * 0.02, true);//approxPolyDP //arcLength计算轮廓周长或曲线长度

	if (approx.size() != 4)
	{
		cout << "The object is not quadrilateral!" << std::endl;
		return -1;
	}

	// Get mass center  
	for (int i = 0; i < corners.size(); i++)
		center += corners[i];
	center *= (1. / corners.size());

	sortCorners(corners, center);  //调用自定义函数
	if (corners.size() == 0){
		cout << "The corners were not sorted correctly!" << std::endl;
		return -1;
	}
	Mat dst = srcImage.clone();

	// Draw lines  
	for (int i = 0; i < lines.size(); i++)
	{
		Vec4i v = lines[i];
		line(dst, Point(v[0], v[1]), Point(v[2], v[3]), CV_RGB(0, 255, 0));
	}

	// Draw corner points  
	circle(dst, corners[0], 3, CV_RGB(255, 0, 0), 2);
	circle(dst, corners[1], 3, CV_RGB(0, 255, 0), 2);
	circle(dst, corners[2], 3, CV_RGB(0, 0, 255), 2);
	circle(dst, corners[3], 3, CV_RGB(255, 255, 255), 2);

	// Draw mass center  
	circle(dst, center, 3, CV_RGB(255, 255, 0), 2);

	Mat quad = Mat::zeros(300, 220, CV_8UC3);

	vector<Point2f> quad_pts;
	quad_pts.push_back(Point2f(0, 0));
	quad_pts.push_back(Point2f(quad.cols, 0));
	quad_pts.push_back(Point2f(quad.cols, quad.rows));
	quad_pts.push_back(Point2f(0, quad.rows));

	Mat transmtx = getPerspectiveTransform(corners, quad_pts); //getPerspectiveTransform由四对点计算透射变换
	warpPerspective(srcImage, quad, transmtx, quad.size()); //warpPerspective对图像进行透视变换 

	imshow("image", dst);
	imshow("quadrilateral", quad);
	waitKey();
	return 0;
}

#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

Mat srcImage, grayImage;
int thresh = 100;
const int threshMaxValue = 255;
RNG rng(12345);

//定义回调函数
void thresh_callback(int, void*);

int main81()
{
	srcImage = imread("./picdemo/shape.png");

	//判断图像是否加载成功
	if (srcImage.empty())
	{
		cout << "图像加载失败" << endl;
		return -1;
	}
	else
	{
		cout << "图像加载成功!" << endl << endl;
	}

	//图像灰度图转化并平滑滤波
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, grayImage, Size(3, 3));

	namedWindow("原图像", WINDOW_AUTOSIZE);
	imshow("原图像", grayImage);

	//创建轨迹条
	createTrackbar("Threshold:", "原图像", &thresh, threshMaxValue, thresh_callback);
	thresh_callback(thresh, 0);
	waitKey(0);

	return 0;
}

void thresh_callback(int, void*)
{
	Mat src_copy = srcImage.clone();
	Mat threshold_output;
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;

	//使用Threshold检测图像边缘
	threshold(grayImage, threshold_output, thresh, 255, THRESH_BINARY);

	//寻找图像轮廓
	findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//寻找图像凸包
	vector<vector<Point>>hull(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		convexHull(Mat(contours[i]), hull[i], false);
	}

	//绘制轮廓和凸包
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
	}

	namedWindow("凸包", WINDOW_AUTOSIZE);
	imshow("凸包", drawing);
}


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

/** @function main */
int main87(int argc, char** argv)
{
	/// Create an image
	const int r = 100;
	Mat src = Mat::zeros(Size(4 * r, 4 * r), CV_8UC1);

	/// Create a sequence of points to make a contour:
	vector<Point2f> vert(6);

	vert[0] = Point(1.5*r, 1.34*r);
	vert[1] = Point(1 * r, 2 * r);
	vert[2] = Point(1.5*r, 2.866*r);
	vert[3] = Point(2.5*r, 2.866*r);
	vert[4] = Point(3 * r, 2 * r);
	vert[5] = Point(2.5*r, 1.34*r);

	/// Draw it in src
	for (int j = 0; j < 6; j++)
	{
		line(src, vert[j], vert[(j + 1) % 6], Scalar(255), 3, 8);
	}

	/// Get the contours
	vector<vector<Point> > contours; vector<Vec4i> hierarchy;
	Mat src_copy = src.clone();

	findContours(src_copy, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	/// Calculate the distances to the contour
	Mat raw_dist(src.size(), CV_32FC1);

	for (int j = 0; j < src.rows; j++)
	{
		for (int i = 0; i < src.cols; i++)
		{
			raw_dist.at<float>(j, i) = pointPolygonTest(contours[0], Point2f(i, j), true);
		}
	}

	double minVal; double maxVal;
	minMaxLoc(raw_dist, &minVal, &maxVal, 0, 0, Mat());
	minVal = abs(minVal); maxVal = abs(maxVal);

	/// Depicting the  distances graphically
	Mat drawing = Mat::zeros(src.size(), CV_8UC3);

	for (int j = 0; j < src.rows; j++)
	{
		for (int i = 0; i < src.cols; i++)
		{
			if (raw_dist.at<float>(j, i) < 0)
			{
				drawing.at<Vec3b>(j, i)[0] = 255 - (int)abs(raw_dist.at<float>(j, i)) * 255 / minVal;
			}
			else if (raw_dist.at<float>(j, i) > 0)
			{
				drawing.at<Vec3b>(j, i)[2] = 255 - (int)raw_dist.at<float>(j, i) * 255 / maxVal;
			}
			else
			{
				drawing.at<Vec3b>(j, i)[0] = 255; drawing.at<Vec3b>(j, i)[1] = 255; drawing.at<Vec3b>(j, i)[2] = 255;
			}
		}
	}

	/// Create Window and show your results
	char* source_window = "Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, src);
	namedWindow("Distance", CV_WINDOW_AUTOSIZE);
	imshow("Distance", drawing);
	
	waitKey(0);
	return(0);
}