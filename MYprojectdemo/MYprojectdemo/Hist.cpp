//#include <opencv2/highgui.hpp>
#include "Image.h"
int main17(int argc, char *argv[])
{
	Mat image,HistImage;
	vector<Mat> bgr_img;
	Mat b_dst, g_dst, r_dst;
	const int channels=0;
	const int histSize = 64;
	float range[] = { 0, 255 };
	const float *ranges = { range };
	image = imread("./picdemo/lena.jpg");
	if (image.empty())
	{
		cout << "Picture load error" << endl;
		return -1;
	}
	imshow("src", image);
	/*计算直方图*/
	split(image, bgr_img);
	calcHist(&bgr_img[0], 1, &channels, Mat(), b_dst, 1, &histSize, &ranges);
	calcHist(&bgr_img[1], 1, &channels, Mat(), g_dst, 1, &histSize, &ranges);
	calcHist(&bgr_img[2], 1, &channels, Mat(), r_dst, 1, &histSize, &ranges);
	/*归一化处理*/
	normalize(b_dst, b_dst, 0, 255, NORM_MINMAX, -1);
	normalize(g_dst, g_dst, 0, 255, NORM_MINMAX, -1);
	normalize(r_dst, r_dst, 0, 255, NORM_MINMAX, -1);
	/*绘制直方图*/
	
	HistImage=Mat(Size(255,255),CV_8UC3,Scalar(0,0,0));
	
	int bins = 256 / histSize;
	for (int index = 1; index < histSize; index++)
	{
		/*line(HistImage, Point((index - 1)*bins, 255 - cvRound(b_dst.at<float>(index - 1))), Point(index*bins, 255 - cvRound(b_dst.at<float>(index))),
			Scalar(255, 0, 0),1,LINE_AA);
		line(HistImage, Point((index - 1)*bins, 255 - cvRound(g_dst.at<float>(index - 1))), Point(index*bins, 255 - cvRound(g_dst.at<float>(index))),
			Scalar(0, 255, 0), 1, LINE_AA);
		line(HistImage, Point((index - 1)*bins, 255 - cvRound(r_dst.at<float>(index - 1))), Point(index*bins, 255 - cvRound(r_dst.at<float>(index))),
			Scalar(0, 0, 255), 1, LINE_AA);*/

		/*line(HistImage, Point((index - 1)*bins, 255 - cvRound(b_dst.at<float>(index - 1))), Point(index*bins, 255 - cvRound(b_dst.at<float>(index))),
		Scalar(255, 0, 0),1,LINE_AA);
		line(HistImage, Point((index - 1)*bins, 255 - cvRound(g_dst.at<float>(index - 1))), Point(index*bins, 255 - cvRound(g_dst.at<float>(index))),
		Scalar(0, 255, 0), 1, LINE_AA);
		line(HistImage, Point((index - 1)*bins, 255 - cvRound(r_dst.at<float>(index - 1))), Point(index*bins, 255 - cvRound(r_dst.at<float>(index))),
		Scalar(0, 0, 255), 1, LINE_AA);*/
		rectangle(HistImage, Rect(bins*(index - 1), 255 - b_dst.at<float>(index), bins, b_dst.at<float>(index)), Scalar(255, 0, 0), 1);
		rectangle(HistImage, Rect(bins*(index - 1), 255 - g_dst.at<float>(index), bins, g_dst.at<float>(index)), Scalar(0, 255, 0), 1);
		rectangle(HistImage, Rect(bins*(index - 1), 255 - r_dst.at<float>(index), bins, r_dst.at<float>(index)), Scalar(0, 0, 255), 1);
	}
	imshow("Hist", HistImage); 
	waitKey(0);
	return 0;
  
}


int main56(int argc, char *argv[])
{
	double confidence = 0.1;
	float thresh = cvRound(255 * confidence);
	Mat image, templateimg,tmp_img,tmp_img_clone,_grayimg,_graytmp;
	templateimg = imread("./picdemo/lenaeye.jpg");
	image = imread("./picdemo/lena.jpg");
	if (image.empty() || templateimg.empty())
	{
		cout << "Picture load error" << endl;
		return -1;
	}
	cvtColor(image, _grayimg, CV_BGR2GRAY);
	cvtColor(templateimg, _graytmp, CV_BGR2GRAY);

	int Size_h = abs(templateimg.rows - image.rows + 1);
	int Size_w = abs(templateimg.cols - image.cols + 1);
	tmp_img.create(Size(Size_w, Size_h), CV_32FC1);

	matchTemplate(_grayimg, _graytmp, tmp_img, TM_CCORR_NORMED);
	tmp_img_clone.create(tmp_img.size(), tmp_img.type());
	//tmp_img_clone = tmp_img.clone();
	normalize(tmp_img, tmp_img, 0, 255);
	double max, min;
	cv::Point minLoc, maxLoc;
	vector<cv::Point3i> _Pvc(0);
	minMaxLoc(tmp_img, &min, &max, &minLoc, &maxLoc);
	float *v_ptr = (float*)tmp_img.data;
	for (int i = 0; i < tmp_img.rows; ++i)
	{
		for (int j = 0; j < tmp_img.cols; ++j)
		{
			//if (thresh <*v_ptr)
			//{
			//	//tmp_img_clone.at<float>(i, j) = tmp_img.at<uchar>(i, j);
			//	_Pvc.push_back(cv::Point3i(i, j, *v_ptr));
			//}
		//	cout << "  " << *v_ptr << '\t';
			cout << "  " << tmp_img.at<float>(i,j)<< '\t';

			v_ptr++;
		}
	}
	cout << "Size of _Pvc  :" << _Pvc.size() << endl;
	rectangle(image, minLoc, maxLoc, Scalar(0, 255, 0), 1);
	imshow("src", tmp_img_clone);
	waitKey(0);
	
}

////////////
Rect imp_rect = Rect(50, 50, 100, 100);
Mat imp_tmp;
int main100()
{
	//加载源图像和模板图像
	int* a1 = new int(10);
	auto_ptr<int> pt(new int(10));
	int *p2 =new int(200);
	cout << "this aoto_ptr's value is " << *pt << "   now get is " << pt.get() << endl;
	pt.reset(p2);
	cout << "this aoto_ptr's value is " << *pt << "   now get is   " << pt.get() <<"  a1 is  "<<*p2<< endl;

	cv::Mat image_source = cv::imread("./picdemo/lena.jpg", cv::IMREAD_GRAYSCALE);
	cv::Mat image_template = cv::imread("./picdemo/lenaeye.jpg", cv::IMREAD_GRAYSCALE);

	cv::Mat image_matched;
	/***/

	
	//模板匹配
	cv::matchTemplate(image_source, image_template, image_matched, cv::TM_CCOEFF_NORMED);

	double minVal, maxVal;
	cv::Point minLoc, maxLoc;
	//寻找最佳匹配位置
	cv::minMaxLoc(image_matched, &minVal, &maxVal, &minLoc, &maxLoc);
	
	
	
	cv::Mat image_color;
	cv::cvtColor(image_source, image_color, CV_GRAY2BGR);
	circle(image_color, minLoc, 3, Scalar(0, 255, 0), 2);
	circle(image_color, maxLoc, 3, Scalar(255, 255, 0), 2);
	imshow("image_source>>>>>", image_color);
	waitKey(0);
	/*cv::circle(image_color,
		cv::Point(maxLoc.x + image_template.cols / 2, maxLoc.y + image_template.rows / 2),
		20,
		cv::Scalar(0, 0, 255),
		2,
		8,
		0);*/
	rectangle(image_color, Rect(minLoc.x, maxLoc.y, image_template.cols, image_template.rows), Scalar(0, 255, 0), 1);
	cv::imshow("source image", image_source);
	cv::imshow("match result", image_matched);
	cv::imshow("target", image_color);
	cv::waitKey(0);

	return 0;
}

int main15()
{
	//加载源图像和模板图像
	ImageOps imgs;
	const int channels = 0;
	Mat hist,cvtoutput,outputimg,tmphist;
	uchar gray = 0;
	double temp = 0;
	const int histSize = 256;
	float min2maxRange[] = { 0, 255 };
	const float* ranges = { min2maxRange };
	cv::Mat image_source = cv::imread("./picdemo/lena.jpg");
	cv::Mat image_template = cv::imread("./picdemo/lenaeye.jpg");
	//cvtColor(image_source, cvtoutput, CV_RGB2GRAY);
	imgs.ImgBGR2GRAY(image_source, cvtoutput);
	calcHist(&cvtoutput, 1, &channels, Mat(), hist, 1, &histSize, &ranges);
	//normalize(hist, hist, 0, 1, NORM_MINMAX);
	tmphist.create(hist.size(), hist.type());
	for (int id = 0; id < hist.rows; ++id)
	{
		tmphist.at<float>(id) = hist.at<float>(id) / (hist.rows*hist.cols);
	}
	//cout << "------------->" << hist.at<float>(16) << endl;
	for (int row = 0; row < cvtoutput.rows; ++row)
	{
		for (int col = 0; col < cvtoutput.cols; ++col)
		{
			temp = 0;
			gray = cvtoutput.at<uchar>(row, col);
			for (uchar kp = 0; kp < gray; ++kp)
			{
				temp += tmphist.at<float>(kp);
			}
			outputimg.at<uchar>(row, col) = saturate_cast<uchar>(255 * temp);
			//cout << "value :=" << (int)piex << endl;
		}
		
	}
	if (!outputimg.empty())
	{
		imshow("Histeq", outputimg);
		waitKey(0);
	}
	return 0;
}


template <typename T,typename Tp>
//template <typename Tp>
double func(T va, Tp vb)
{
	Tp vc = va + vb;
	return vc;
}


class operatorcg{
	friend ostream& operator<< (ostream& output, operatorcg& oop);
private:
	int a;
	int b;
public:
	void SetValue(int a, int b)
	{
		this->a = a;
		this->b = b;
	}

};
ostream& operator<< (ostream& output, operatorcg& oop)
{
	output << "oop.a=" << oop.a << "    b=" << oop.b << endl;
	return output;
}
int main25(void)
{
	operatorcg oop,oop2;
	oop.SetValue(10, 15);
	oop2.SetValue(11, 16);
	cout << oop <<"\t"<< oop2;
	system("pause");
	return 0;
}
#include <sstream>
int main22()
{
	//std::getline()
	string chstr = "liunjuhbhfvfvcd";
	stringstream ss;
	ss.clear();
	char ch = '0';
	ss.str(chstr);
	while (!ss.fail())
	{
		//ss >> ch;
		cout << ch << '\t';
	}


	system("pause");
	return 0;
}



// vector::reserve
#include <iostream>
#include <vector>

int main26()
{
	std::vector<int>::size_type sz;

	std::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i = 0; i<100; ++i) {
		foo.push_back(i);
		if (sz != foo.capacity()) {
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	std::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);   // this is the only difference with foo above
	std::cout << "making bar grow:\n";
	for (int i = 0; i<100; ++i) {
		bar.push_back(i);
		if (sz != bar.capacity()) {
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
	system("pause");
	return 0;
}


int main26(int argc, char *argv)
{

	vector<int> intvec;
	cout << "get the intvec's size  " << intvec.size()<< endl;
	cout << "get the intvec's captial  " << intvec.capacity() << endl;
	//intvec.reserve(2);
	for (int id = 0; id < 10; id++)
	{
		intvec.push_back(id);
	}
	cout << "get the intvec's size  " << intvec.size() << endl;
	cout << "get the intvec's captial  " << intvec.capacity() << endl;
	for (int id = 0; id < 4; id++)
	{
		intvec.push_back(id);
	}
	cout << "get the intvec's size  " << intvec.size() << endl;
	cout << "get the intvec's captial  " << intvec.capacity() << endl;
	intvec.reserve(100);
	cout << "get the intvec's size  " << intvec.size() << endl;
	cout << "get the intvec's captial  " << intvec.capacity() << endl;
	system("pause");
	return 0;
	
}
#include<sstream>
int sum(int a, int b )
{
	return 0;
}
int main28(int argc, char *argv)
{
#ifdef strv
	string teststr = "dfdvjfjbjgkbnfbvcl#vfbkng";
	/*stringstream ss;
	ss.str(teststr);*/
	char ch = '0';
	
		string::size_type offisetpre=teststr.find_first_of('#', 0);
		string::size_type offisetlst = teststr.find_last_of('#',teststr.npos);
		cout << "   pre   " << offisetpre << "   lst   " << offisetlst << endl;
		offisetpre = teststr.find("#v", 0);/*从前向后找*/
		 offisetlst = teststr.rfind("#v", teststr.npos);/*从后向前找*/
		cout << "   pre   " << offisetpre << "   lst   " << offisetlst << endl;
#endif
		int a = 0, b = 0, c = 0;
		sum(a, b);
		cout << "c=  " << c << endl;
	system("pause");
	return 0;
}


//#include <windows.h>
//#include <tchar.h>
//#include <stdio.h>
//void main27(int argc, TCHAR *argv[])
//{
//	WIN32_FIND_DATA FindFileData;
//	HANDLE hFind;
//
//	if (argc != 2)
//	{
//		_tprintf(TEXT("Usage: %s [target_file]\n"), argv[0]);
//		return;
//	}
//
//	_tprintf(TEXT("Target file is %s\n"), argv[1]);
//	hFind = FindFirstFile(argv[1], &FindFileData);
//	if (hFind == INVALID_HANDLE_VALUE)
//	{
//		printf("FindFirstFile failed (%d)\n", GetLastError());
//		return;
//	}
//	else
//	{
//		_tprintf(TEXT("The first file found is %s\n"),
//			FindFileData.cFileName);
//		FindClose(hFind);
//	}
//}
//
//int main29(int argc, char *argv[])
//{
//	WIN32_FIND_DATA dataofFile;
//	HANDLE opshandle;
//	printf("Target file is %s./n", argv[1]);
//	opshandle = FindFirstFile(argv[1], &dataofFile);
//	if (INVALID_HANDLE_VALUE == opshandle)
//	{
//		printf("file  invalid");
//	}
//	else{
//
//		printf("the first file found is %s", dataofFile.cFileName);
//	}
//		
//	system("pause");
//	return 0;
//}

#if 0
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <vector>  
#include <iostream>  
#include "f:/work/mydemo/MYprojectdemo/include/opencv2/features2d.hpp"
using namespace cv;
using namespace std;
Mat src, frameImg;
int width;
int height;
vector<Point> srcCorner(4);
vector<Point> dstCorner(4);

static bool createDetectorDescriptorMatcher(const string& detectorType, const string& descriptorType, const string& matcherType,
	Ptr<FeatureDetector>& featureDetector,
	Ptr<DescriptorExtractor>& descriptorExtractor,
	Ptr<DescriptorMatcher>& descriptorMatcher)
{
	cout << "< Creating feature detector, descriptor extractor and descriptor matcher ..." << endl;
	if (detectorType == "SIFT" || detectorType == "SURF")
		initModule_nonfree();
	featureDetector = FeatureDetector::create(detectorType);
	descriptorExtractor = DescriptorExtractor::create(descriptorType);
	descriptorMatcher = DescriptorMatcher::create(matcherType);
	cout << ">" << endl;
	bool isCreated = !(featureDetector.empty() || descriptorExtractor.empty() || descriptorMatcher.empty());
	if (!isCreated)
		cout << "Can not create feature detector or descriptor extractor or descriptor matcher of given types." << endl << ">" << endl;
	return isCreated;
}


bool refineMatchesWithHomography(const std::vector<cv::KeyPoint>& queryKeypoints,
	const std::vector<cv::KeyPoint>& trainKeypoints,
	float reprojectionThreshold,
	std::vector<cv::DMatch>& matches,
	cv::Mat& homography)
{
	const int minNumberMatchesAllowed = 4;
	if (matches.size() < minNumberMatchesAllowed)
		return false;
	// Prepare data for cv::findHomography    
	std::vector<cv::Point2f> queryPoints(matches.size());
	std::vector<cv::Point2f> trainPoints(matches.size());
	for (size_t i = 0; i < matches.size(); i++)
	{
		queryPoints[i] = queryKeypoints[matches[i].queryIdx].pt;
		trainPoints[i] = trainKeypoints[matches[i].trainIdx].pt;
	}
	// Find homography matrix and get inliers mask    
	std::vector<unsigned char> inliersMask(matches.size());
	homography = cv::findHomography(queryPoints,
		trainPoints,
		CV_FM_RANSAC,
		reprojectionThreshold,
		inliersMask);
	std::vector<cv::DMatch> inliers;
	for (size_t i = 0; i<inliersMask.size(); i++)
	{
		if (inliersMask[i])
			inliers.push_back(matches[i]);
	}
	matches.swap(inliers);
	Mat homoShow;
	drawMatches(src, queryKeypoints, frameImg, trainKeypoints, matches, homoShow, Scalar::all(-1), CV_RGB(255, 255, 255), Mat(), 2);
	imshow("homoShow", homoShow);
	return matches.size() > minNumberMatchesAllowed;

}


bool matchingDescriptor(const vector<KeyPoint>& queryKeyPoints, const vector<KeyPoint>& trainKeyPoints,
	const Mat& queryDescriptors, const Mat& trainDescriptors,
	Ptr<DescriptorMatcher>& descriptorMatcher,
	bool enableRatioTest = true)
{
	vector<vector<DMatch>> m_knnMatches;
	vector<DMatch>m_Matches;

	if (enableRatioTest)
	{
		cout << "KNN Matching" << endl;
		const float minRatio = 1.f / 1.5f;
		descriptorMatcher->knnMatch(queryDescriptors, trainDescriptors, m_knnMatches, 2);
		for (size_t i = 0; i<m_knnMatches.size(); i++)
		{
			const cv::DMatch& bestMatch = m_knnMatches[i][0];
			const cv::DMatch& betterMatch = m_knnMatches[i][1];
			float distanceRatio = bestMatch.distance / betterMatch.distance;
			if (distanceRatio < minRatio)
			{
				m_Matches.push_back(bestMatch);
			}
		}

	}
	else
	{
		cout << "Cross-Check" << endl;
		Ptr<cv::DescriptorMatcher> BFMatcher(new cv::BFMatcher(cv::NORM_HAMMING, true));
		BFMatcher->match(queryDescriptors, trainDescriptors, m_Matches);
	}
	Mat homo;
	float homographyReprojectionThreshold = 1.0;
	bool homographyFound = refineMatchesWithHomography(
		queryKeyPoints, trainKeyPoints, homographyReprojectionThreshold, m_Matches, homo);

	if (!homographyFound)
		return false;
	else
	{
		if (m_Matches.size()>10)
		{
			std::vector<Point2f> obj_corners(4);
			obj_corners[0] = cvPoint(0, 0); obj_corners[1] = cvPoint(src.cols, 0);
			obj_corners[2] = cvPoint(src.cols, src.rows); obj_corners[3] = cvPoint(0, src.rows);
			std::vector<Point2f> scene_corners(4);
			perspectiveTransform(obj_corners, scene_corners, homo);
			line(frameImg, scene_corners[0], scene_corners[1], CV_RGB(255, 0, 0), 2);
			line(frameImg, scene_corners[1], scene_corners[2], CV_RGB(255, 0, 0), 2);
			line(frameImg, scene_corners[2], scene_corners[3], CV_RGB(255, 0, 0), 2);
			line(frameImg, scene_corners[3], scene_corners[0], CV_RGB(255, 0, 0), 2);
			return true;
		}
		return true;
	}


}
int main()
{
	string filename = "box.png";
	src = imread(filename, 0);
	width = src.cols;
	height = src.rows;
	string detectorType = "SIFT";
	string descriptorType = "SIFT";
	string matcherType = "FlannBased";
	
	Ptr<FeatureDetector> featureDetector;
	Ptr<DescriptorExtractor> descriptorExtractor;
	Ptr<DescriptorMatcher> descriptorMatcher;
	if (!createDetectorDescriptorMatcher(detectorType, descriptorType, matcherType, featureDetector, descriptorExtractor, descriptorMatcher))
	{
		cout << "Creat Detector Descriptor Matcher False!" << endl;
		return -1;
	}
	//Intial: read the pattern img keyPoint  
	vector<KeyPoint> queryKeypoints;
	Mat queryDescriptor;
	featureDetector->detect(src, queryKeypoints);
	descriptorExtractor->compute(src, queryKeypoints, queryDescriptor);

	VideoCapture cap(0); // open the default camera  
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
	if (!cap.isOpened())  // check if we succeeded  
	{
		cout << "Can't Open Camera!" << endl;
		return -1;
	}
	srcCorner[0] = Point(0, 0);
	srcCorner[1] = Point(width, 0);
	srcCorner[2] = Point(width, height);
	srcCorner[3] = Point(0, height);

	vector<KeyPoint> trainKeypoints;
	Mat trainDescriptor;

	Mat frame, grayFrame;
	char key = 0;

	//	frame = imread("box_in_scene.png");  
	while (key != 27)
	{
		cap >> frame;
		if (!frame.empty())
		{
			frame.copyTo(frameImg);
			printf("%d,%d\n", frame.depth(), frame.channels());
			grayFrame.zeros(frame.rows, frame.cols, CV_8UC1);
			cvtColor(frame, grayFrame, CV_BGR2GRAY);
			trainKeypoints.clear();
			trainDescriptor.setTo(0);
			featureDetector->detect(grayFrame, trainKeypoints);

			if (trainKeypoints.size() != 0)
			{
				descriptorExtractor->compute(grayFrame, trainKeypoints, trainDescriptor);

				bool isFound = matchingDescriptor(queryKeypoints, trainKeypoints, queryDescriptor, trainDescriptor, descriptorMatcher);
				imshow("foundImg", frameImg);

			}
		}
		key = waitKey(1);
	}
	cap.release();
	return 0;
}
#endif

