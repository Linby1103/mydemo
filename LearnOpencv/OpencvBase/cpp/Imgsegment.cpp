#include "testopencv.h" 
int IterThres(cv::Mat &mat, int thres_val,int count)
{
	
	if (count > 100) return thres_val;
	if (!mat.data) return -1;
	int  highthres, lowthres,count0,count1;

	int thres = 0;
	if (thres_val < 0)
		thres = abs(thres_val);
	highthres = lowthres = count0 = count1=0;
	for (int i = 0; i < mat.rows; ++i)
	{
		for (int j = 0; j < mat.cols; ++j)
		{
			if (mat.at<uchar>(i, j) >= thres_val)
			{
				highthres += mat.at<uchar>(i, j);
				count0++;
			}
			else
			{
				lowthres += mat.at<uchar>(i, j);
				count1++;
			}
		}
	}
	if (count0 == 0) highthres = 0;
	else highthres /= count0;
	if (count1 == 0) lowthres = 0;
	else lowthres /= count1;
	thres = (highthres + lowthres) / 2;
	if (thres<thres_val) return thres;
	IterThres(mat, thres, ++count);

}

int my_otsu(cv::Mat &src)
{
	if (src.empty())
	{
		printf("Source Image Is NULL!");
		return -1;
	}
	cv::Mat graymat;
	int best_thres = 0;
	if (src.channels() != 1)	cvtColor(src, graymat, CV_BGR2GRAY);
	else graymat = src.clone();
	int smunpiexl = graymat.cols*graymat.rows;
	const int thres = 255;
	float piexl_prob[thres] = { 0.f };
	int piexl_num[thres] = { 0 };
	float maxsigma = 0.f;
	//统计C0,C1区域像素出现的频数
	for (int i = 0; i < graymat.rows; i++)
	{
		for (int j = 0; j < graymat.cols; j++)
		{
			piexl_num[graymat.at<uchar>(i, j)]++;
		}
	}
	//统计各个灰度级出现的概率
	for (int p = 0; p < thres; ++p)
	{
		piexl_prob[p] = piexl_num[p]*1.0f / smunpiexl;
	}
	float prob_low = 0.f,prob_hight = 0.f,lowave_gray=0.f,highave_gray=0.f;
	for (int k = 0; k < thres; ++k)
	{
		prob_low = prob_hight = lowave_gray = highave_gray= 0.f;
		
		for (int m = 0; m < thres; ++m)
		{
			if (m < k)
			{
				prob_low += piexl_prob[m];
				lowave_gray += m*piexl_prob[m];
			}
			else
			{
				prob_hight += piexl_prob[m];
				highave_gray += m*piexl_prob[m];
			}
		}
		float _prob_low = lowave_gray / prob_low;
		float _prob_hight = highave_gray / prob_hight;
		float sigma = prob_low*prob_hight*(_prob_hight - _prob_low)*(_prob_hight - _prob_low);
		if (sigma > maxsigma)
		{
			maxsigma = sigma;
			best_thres = k;
		}
	}
	return best_thres;
}
int main(int argc, char* argv)
{
	cv::Mat img = imread("D:/Work/code/LearnOpencv/OpencvBase/img/0.jpg");
	cv::Mat graymat;
	cvtColor(img, graymat,CV_BGR2GRAY);
	//int thres = IterThres(graymat, 180,0);

	//cout << thres << endl;
	int thres = my_otsu(graymat);
	for (int i = 0; i < graymat.rows; i++)
	{
		for(int j = 0; j < graymat.cols;j++)
		{
			if (graymat.at<uchar>(i, j)>thres)
				graymat.at<uchar>(i, j) = 255;
			else graymat.at<uchar>(i, j) = 0;
		}
	}
	imshow("thres", graymat);
	waitKey(0);
	getchar();
	return 0;
}