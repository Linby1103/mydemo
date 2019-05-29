#include "ImageInfo.h"
void pImgInfo::reset()
{
	image_width = 0;
	image_height = 0;
	image_channels = -1;
}
/*打印image详细*/
void pImgInfo::printInfo(Mat Arrarinput, string imgName)
{
	Mat PthisImg = Arrarinput;
	if (!PthisImg.data&&imgName.empty())
	{
		std::cout << "data error-->exit" << std::endl;
	}
	image_width = PthisImg.rows;
	image_height = PthisImg.cols;
	image_channels = PthisImg.channels();
	cv::imshow(imgName, PthisImg);
	std::cout << "press any key to continue:" << std::endl;
	waitKey(0);
	cv::destroyWindow(imgName);
}
#include <sstream>
int main09()
{
	stringstream stt("1 123");
	stt.str("2 234");
	cout << "stt=" << stt.str() << endl;
	
	int recva;
	double recvb;
	stt >> recva;
	stt >> recvb;
	cout << "recva  " << recva << "   rcevb  " << recvb << endl;
	string line, str;
	while (getline(cin, line))//从终端接收一行字符串，并放入字符串line中   
	{
		stt.str(line);//把line中的字符串存入字符串流中   
		while (stt >> str)//每次读取一个单词（以空格为界），存入str中   
		{
			cout << str << endl;

		}
	}
	getchar();
	return 0;
}





	
	TarModel* _tm;
	int main99()
	{
		_tm = Creator<TarModel>::create("rot");
		getchar();
		return  0;
	}


	/*class stra{


	public:
		static int vax;
		void setvax(int vax){ this->vax = vax; }
		void print(){ std::cout << "vax   " << vax << endl; }
	};

	int  stra::vax = 0;
	int main()
	{
		stra sta;
		sta.setvax(100);
		sta.print();
		getchar();
		return 0;
	}*/

	class TmodelInfo{

	public:
		//bool readfile(FILE *file);
		//FILE *file;
		int vbc;
	private:
		static double xcv;
	};

	//double TmodelInfo::xcv = 0;

	int main_()
	{
		char *imageSrc = "./picdemo/lena.jpg";
		Mat matImage = imread(imageSrc, -1);
		IplImage *iplImage = cvLoadImage(imageSrc, -1);

		if (matImage.data == 0 || iplImage->imageData == 0)
		{
			cout << "图片加载失败" << endl;
			return -1;
		}

		cv::rectangle(matImage, cvPoint(20, 200), cvPoint(200, 300), Scalar(255, 0, 0), 1, 1, 0);
		//Rect(int a,int b,int c,int d)a,b为矩形的左上角坐标,c,d为矩形的长和宽
		cv::rectangle(matImage, Rect(100, 300, 20, 200), Scalar(0, 0, 255), 1, 1, 0);
		cvRectangle(iplImage, cvPoint(20, 200), cvPoint(200, 300), Scalar(0, 255, 255), 1, 1, 0);

		imshow("matImage", matImage);
		cvShowImage("IplImage", iplImage);
		waitKey();
		return 0;
	}

//clustering algorithm
	/*
	P1(0,0)
	P2(1,2)
	P3(3,1)
	P3(8,8)
	P5(9,10)
	P6(10,7)
	*/
	const int K = 3;
	int ComputMindist(vector<Point2i> group, Point2i vecPot)
	{
		int lable = 0;//标签值
		float dismin = cv::norm((group[0] - vecPot));
		
		for (int i = 1; i < K; ++i)
		{
			Point2i subpt = group[i] - vecPot;
			float dist = cv::norm(subpt);
			if (dismin > dist) { lable = i; }
			else   dismin = dist;
		}
		return lable;
	}
	void clacCenter(vector<Point2i> Vecgroup[], vector<Point2i> &group)
	{
		group.clear();
		int Xderiva=0, Yderiva = 0;
		for (int i = 0; i < K; ++i)
		{
			Xderiva = Yderiva = 0;
			for (int j = 0; j < Vecgroup[i].size(); ++j)
			{
				/*sum of X direction derivatives*/
				Xderiva += Vecgroup[i][j].x;
				/*sum of Y direction derivatives*/
				Yderiva += Vecgroup[i][j].y;
			}
			Xderiva /= Vecgroup[i].size();
			Yderiva /= Vecgroup[i].size();
			group.push_back((Point(cvRound(Xderiva), cvRound(Yderiva))));
		}
	}
	/*计算每个对象与这些中心对象的距离*/
	float GetConvergent(vector<Point2i> Vecgroup[], vector<Point2i> group)
	{
		float Sumdist = 0;
		for (int i = 0; i < K; ++i)
		{
			for (int j = 0; j < Vecgroup[i].size(); ++j)
			{
				Point2i pt = (group[i] - Vecgroup[i][j]);
					Sumdist += cv::norm(pt);
			}
		}
		return Sumdist;
	}
	/****************/
	Point2i getMeans(vector<Point2i> group){

		int num = group.size();
		double meansX = 0, meansY = 0;
		Point2i t;
		for (int i = 0; i < num; i++)
		{
			meansX += group[i].x;
			meansY += group[i].y;
		}
		t.x = meansX;
		t.y = meansY;
		return t;
		//cout<<"sum:"<<sum<<endl;
	}
	void clustalg(vector<Point2i> vecPot)
	{
		bool debug = true;
		vector<Point2i> Group;
		vector<Point2i> Vecgroup[K];
		
		Point2i mumba,mumbb, mumbc;
		float min = 100, max = 0;
		/*1 第一次以P1,P2为质心  K=2*/
		for (int k = 0; k < K; ++k)
		{
			Group.push_back(vecPot[k]);
		}
		/*2  根据默认质心对数据的做初步的分类*/
		for (int j = 0; j < vecPot.size(); ++j)
		{
			int lable = ComputMindist(Group, vecPot[j]);
			Vecgroup[lable].push_back(vecPot[j]);
		}
		if (debug)
		{
			for (int id = 0; id < K; ++id)
			{
				for (int i = 0; i < Vecgroup[id].size(); ++i)
					cout << "第 " << id << "族 " << " 第 " << i << " 个 数据 " << Vecgroup[id][i] << endl;
			}
		}
		float cur_converg = -1;
		float new_converg = GetConvergent(Vecgroup, Group);
		/*迭代*/
		while (abs(cur_converg - new_converg) >= 1)
			/* 3 重新分配质心*/
		{
			for (int i = 0; i < K; ++i)
			{
				Point2i pt;
				//Group.push_back(pt);
				pt = getMeans(Vecgroup[i]);
				Group.push_back(pt);
			}
			clacCenter(Vecgroup, Group);

			cur_converg = new_converg;
			new_converg = GetConvergent(Vecgroup, Group);
			for (int i = 0; i < K; ++i)
				Vecgroup[i].clear();
			for (int j = 0; j < vecPot.size(); ++j)
			{
				int lable = ComputMindist(Group, vecPot[j]);
				/*重新分类*/
				Vecgroup[lable].push_back(vecPot[j]);
			}
			for (int id = 0; id < K; ++id)
			{
				for (int i = 0; i < Vecgroup[id].size(); ++i)
					cout << "第 " << id << "族 " << " 第 " << i << " 个 数据 " << Vecgroup[id][i] << endl;
			}
		}
		
	}
	int main123(int argc, char* argv[])
	{
		vector<Point2i> VecPt;
		VecPt.push_back(Point2i(0, 12));
		VecPt.push_back(Point2i(12, 2));
		VecPt.push_back(Point2i(31, 11));
		VecPt.push_back(Point2i(1, 1));
		VecPt.push_back(Point2i(19, 10));
		VecPt.push_back(Point2i(80, 7));
		if (VecPt.data())
			//clustalg(VecPt);
		getchar();
		return 0;
	}

	int main_xc(int argc, char *argv[])
	{
		Mat image = imread("./picdemo/lena.jpg");
		if (!image.data)
			return -1;
		Mat im_color;
		applyColorMap(image, im_color, 11);
		imshow("colormap", im_color);
		waitKey(0);
		return 0;
	}

	int main_vbn(int argc, char *argv[])
	{
		Mat image = imread("./picdemo/lena.jpg");
		Mat perspective;
		Point2f objectivePoint[4], imagePoint[4];
		imagePoint[0].x = 10.0;  imagePoint[0].y = 457.0;
		imagePoint[1].x = 395.0; imagePoint[1].y = 291.0;
		imagePoint[2].x = 624.0; imagePoint[2].y = 291.0;
		imagePoint[3].x = 1000.0; imagePoint[3].y = 457.0;
		double moveValuex = 0.0;
		double moveValuey = 0.0;
		objectivePoint[0].x = 46.0 + moveValuex;  objectivePoint[0].y = 920.0 + moveValuey;
		objectivePoint[1].x = 46.0 + moveValuex; objectivePoint[1].y = 100.0 + moveValuey;
		objectivePoint[2].x = 600.0 + moveValuex; objectivePoint[2].y = 100.0 + moveValuey;
		objectivePoint[3].x = 600.0 + moveValuex; objectivePoint[3].y = 920 + moveValuey;
		Mat tranform = getPerspectiveTransform(objectivePoint, imagePoint);
		warpPerspective(image, perspective, tranform, Size(image.rows, image.cols), cv::INTER_LINEAR | cv::WARP_INVERSE_MAP);
		cv::imwrite("./picdemo/perspectiveImage.jpg", perspective);
		imshow("perspectiveImage", perspective);
		imshow("srouce", image);
		waitKey(0);
		return 0;
	}

	//获取	ROI区域
	void CorrentPoint(cv::Mat &src, cv::Point &t1)
	{
		if (src.empty())
		{
			cout << "Image is Empty" << endl;
			return;
		}
		int width = src.cols;
		int height = src.rows;
		if (t1.x > width - 1)
			t1.x = width - 1;
		if (t1.y > height - 1)
			t1.y = height - 1;
	}
	cv::Mat SetRoiImage(cv::Mat &src,cv::Mat &roiimg,int xpos,int ypos)
	{
		if (src.empty() || roiimg.empty())
		{
			cout << "Image is Null" << endl;
			return roiimg;
		}
		int img_height = src.rows;
		int img_width = src.cols;
		cv::Rect roirect = cv::Rect(xpos, ypos, roiimg.cols, roiimg.rows);
		cv::Point ptl = roirect.tl();
		cv::Point pbr = roirect.br();
		CorrentPoint(src, ptl);
		CorrentPoint(src, pbr);
		roirect=cv::Rect(ptl, pbr);
		roiimg.copyTo(src(roirect));
	}


#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
	using  namespace std;
	using namespace cv;
	bool GetGrayMatrix(cv::Mat src, std::vector<vector<int> >& output, cv::Point dispt1, cv::Point dispt2)
	{
		cv::Mat graymat;
		if (src.empty())
			return false;
		if (src.channels() == 3) cvtColor(src, graymat, CV_8UC1);
		else graymat = src.clone();
		//统计灰度级数
		uchar maxgrayval = 0;
		for (int i = 0; i < graymat.rows; i++)
		{
			for (int j = 0; j < graymat.cols; j++)
			{
				uchar gray = graymat.at<uchar>(i, j);
				if (gray>maxgrayval)
					maxgrayval = gray;
			}
		}
		//创建共生矩阵
		std::vector<vector<int> > vecrow;
		std::vector<int> vecint(maxgrayval + 1, 0);
		for (int i = 0; i < maxgrayval + 1; i++)
		{
			vecrow.push_back(vecint);
		}
		for (int i = 0; i < graymat.rows; i++)
		{
			for (int j = 0; j < graymat.cols; j++)
			{
				uchar gray = graymat.at<uchar>(i, j);
				int i2pt1 = i + dispt1.x;
				int j2pt2 = j + dispt1.y;
				if (i2pt1 >= 0 && i2pt1 < graymat.cols&&j2pt2 >= 0 && j2pt2 < graymat.rows)
				{
					uchar i2dispt1gray = graymat.at<uchar>(i2pt1, j2pt2);
					vecrow[gray][i2dispt1gray]++;
				}
				int i2pt3 = i + dispt2.x;
				int j2pt4 = j + dispt2.y;
				if (i2pt3 >= 0 && i2pt3 < graymat.cols&&j2pt4 >= 0 && j2pt4 < graymat.rows)
				{
					uchar i2dispt1gray = graymat.at<uchar>(i2pt3, j2pt4);
					vecrow[gray][i2dispt1gray]++;
				}
			}

		}
		output = vecrow;




		return true;
	}

	int main()
	{
		ofstream file;
		cv::Mat src = imread("/home/code/imgdir/lena.jpg");
		std::vector<std::vector<int> > output;
		output.clear();

		if (src.empty())
		{
			cout << "Image is Empty!" << endl;
			return -1;
		}
		GetGrayMatrix(src, output, cv::Point(2, 2), cv::Point(4, 4));
		file.open("/home/code/imgdir/file.txt", std::ofstream::out,0);
		if (!file.is_open())
		{
			cout << "Open File Failed!" << endl;
			return -1;
		}
		for (int inx = 0; inx<output.size(); inx++)
		for (int j = 0; j<output[inx].size(); j++)
			//cout << output[inx][j] << "    ";
			file << output[inx][j] << "    ";
		file.close();
		return 0;
	}









	int main_1103()
	{
		// get original image.
		cv::Mat originalImage = cv::imread("./picdemo/big_0.jpg");

		// perspective image.
		cv::Mat perspectiveImage;

		// perspective transform
		cv::Point2f objectivePoints[4], imagePoints[4];

		// original image points.
		imagePoints[0].x = 10.0; imagePoints[0].y = 457.0;
		imagePoints[1].x = 395.0; imagePoints[1].y = 291.0;
		imagePoints[2].x = 624.0; imagePoints[2].y = 291.0;
		imagePoints[3].x = 1000.0; imagePoints[3].y = 457.0;

		// objective points of perspective image.
		// move up the perspective image : objectivePoints.y - value .
		// move left the perspective image : objectivePoints.x - value.
		double moveValueX = 0.0;
		double moveValueY = 0.0;

		objectivePoints[0].x = 46.0 + moveValueX; objectivePoints[0].y = 920.0 + moveValueY;
		objectivePoints[1].x = 46.0 + moveValueX; objectivePoints[1].y = 100.0 + moveValueY;
		objectivePoints[2].x = 600.0 + moveValueX; objectivePoints[2].y = 100.0 + moveValueY;
		objectivePoints[3].x = 600.0 + moveValueX; objectivePoints[3].y = 920.0 + moveValueY;

		cv::Mat transform = cv::getPerspectiveTransform(objectivePoints, imagePoints);

		// perspective.
		cv::warpPerspective(originalImage,
			perspectiveImage,
			transform,
			cv::Size(originalImage.rows, originalImage.cols),
			cv::INTER_LINEAR | cv::WARP_INVERSE_MAP);

		 cv::imshow("perspective image", perspectiveImage);
		 cvWaitKey(0);

		cv::imwrite("perspectiveImage.png", perspectiveImage);

		return 0;
	}

	int main_wirte(int argc, char *argv[])
	{
		FileStorage fs("C:\\Users\\xz\\Downloads\\20180606\\0A47ACF364674E4DBD0636A26F55E1E1\\3ED8CFBA4AC84B04BA9ACA5C62D52B8D\\checkpoint\\template\\test.xml",FileStorage::WRITE);
	//	if (fs.isOpened())
		{
			int num1, num2;
			num1 = 3, num2 = 4;
			fs << "num1" << num1;
			fs << "num2" << num2;
			
			
			Mat A(4, 5, CV_32FC1, Scalar(10));
			fs << "A" << A;
			fs.release();
		}

		return 0;
	}


	int main_111(int argc, char *argv[])
	{
		FileStorage fs("C:\\Users\\xz\\Downloads\\20180606\\0A47ACF364674E4DBD0636A26F55E1E1\\3ED8CFBA4AC84B04BA9ACA5C62D52B8D\\checkpoint\\template\\test.xml", FileStorage::READ);
			if (fs.isOpened())
		{
				cv::Mat img(Size(4, 5), CV_32FC1);
				fs["A"] >> img;
				for (int i = 0; i < img.rows; ++i)
				{
					for (int j = 0; j < img.cols; ++j)
						cout << img.at<float>(i,j)<<"   ";
				}
				cout << endl;
		}
			getchar();
		return 0;
	}
	int main_110()
	{
		Mat img = imread("F:/work/mydemo/MYprojectdemo/MYprojectdemo/picdemo/lena.jpg");
		if (img.empty()) return -1;
		vector<Mat> splitMat;
		split(img, splitMat);
		Mat r_split = splitMat.at(2);
		Scalar va = cv::sum(r_split);
		cout << "value    " << va << endl;

		getchar();
		return 0;
	}