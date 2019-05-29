#include <iostream>
#include "k-means.h"
using namespace std;
#if 0
int mainxx()
{
    double data[] = {
        0.0, 0.2, 0.4,
        0.3, 0.2, 0.4,
        0.4, 0.2, 0.4,
        0.5, 0.2, 0.4,
        5.0, 5.2, 8.4,
        6.0, 5.2, 7.4,
        4.0, 5.2, 4.4,
        10.3, 10.4, 10.5,
        10.1, 10.6, 10.7,
        11.3, 10.2, 10.9
    };

    const int size = 10; //Number of samples
    const int dim = 3;   //Dimension of feature
    const int cluster_num = 4; //Cluster number

    KMeans* kmeans = new KMeans(dim,cluster_num);
    int* labels = new int[size];
    kmeans->SetInitMode(KMeans::InitUniform);
	kmeans->Cluster(data,size,labels);

	for(int i = 0; i < size; ++i)
	{
	    printf("%f, %f, %f belongs to %d cluster\n", data[i*dim+0], data[i*dim+1], data[i*dim+2], labels[i]);
	}
	getchar();
	delete []labels;
	delete kmeans;

    return 0;
}
#endif
/****************************************************/
/*kmeans算法实现（此处只考虑元组只有两个属性的情况）
*@File:k_means.cpp
*@Author:Cai0538
*@Create:2011-12-10
*@Last Modified:2011-12-10
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#define k 3
using namespace std;
//存放元组的属性信息
struct Tuple{
	float attr1;
	float attr2;
};
//计算两个元组间的欧几里距离
float getDistXY(Tuple t1, Tuple t2)
{
	return sqrt((t1.attr1 - t2.attr1) * (t1.attr1 - t2.attr1) + (t1.attr2 - t2.attr2) * (t1.attr2 - t2.attr2));
}

//根据质心，决定当前元组属于哪个簇
int clusterOfTuple(Tuple means[], Tuple tuple){
	float dist = getDistXY(means[0], tuple);
	float tmp;
	int label = 0;//标示属于哪一个簇
	for (int i = 1; i<k; i++){
		tmp = getDistXY(means[i], tuple);
		if (tmp<dist) { dist = tmp; label = i; }
	}
	return label;
}
//获得给定簇集的平方误差
float getVar(vector<Tuple> clusters[], Tuple means[]){
	float var = 0;
	for (int i = 0; i < k; i++)
	{
		vector<Tuple> t = clusters[i];
		for (int j = 0; j< t.size(); j++)
		{
			var += getDistXY(t[j], means[i]);
		}
	}
	//cout<<"sum:"<<sum<<endl;
	return var;

}
//获得当前簇的均值（质心）
Tuple getMeans(vector<Tuple> cluster){

	int num = cluster.size();
	double meansX = 0, meansY = 0;
	Tuple t;
	for (int i = 0; i < num; i++)
	{
		meansX += cluster[i].attr1;
		meansY += cluster[i].attr2;
	}
	t.attr1 = meansX / num;
	t.attr2 = meansY / num;
	return t;
	//cout<<"sum:"<<sum<<endl;


}
void KMeans(vector<Tuple> tuples){
	vector<Tuple> clusters[k];
	Tuple means[k];
	int i = 0;
	//默认一开始将前K个元组的值作为k个簇的质心（均值）
	for (i = 0; i<k; i++){
		means[i].attr1 = tuples[i].attr1;
		means[i].attr2 = tuples[i].attr2;
	}
	int lable = 0;
	//根据默认的质心给簇赋值
	for (i = 0; i != tuples.size(); ++i){
		lable = clusterOfTuple(means, tuples[i]);
		clusters[lable].push_back(tuples[i]);
	}
	//输出刚开始的簇
	for (lable = 0; lable<3; lable++){
		cout << "第" << lable + 1 << "个簇：" << endl;
		vector<Tuple> t = clusters[lable];
		for (i = 0; i< t.size(); i++)
		{
			cout << "(" << t[i].attr1 << "," << t[i].attr2 << ")" << "   ";
		}
		cout << endl;
	}
	float oldVar = -1;
	float newVar = getVar(clusters, means);
	while (abs(newVar - oldVar) >= 1) //当新旧函数值相差不到1即准则函数值不发生明显变化时，算法终止
	{

		for (i = 0; i < k; i++) //更新每个簇的中心点
		{
			means[i] = getMeans(clusters[i]);
			//cout<<"means["<<i<<"]:"<<means[i].attr1<<"  "<<means[i].attr2<<endl;
		}
		oldVar = newVar;
		newVar = getVar(clusters, means); //计算新的准则函数值
		for (i = 0; i < k; i++) //清空每个簇
		{
			clusters[i].clear();
		}
		//根据新的质心获得新的簇
		for (i = 0; i != tuples.size(); ++i){
			lable = clusterOfTuple(means, tuples[i]);
			clusters[lable].push_back(tuples[i]);
		}
		//输出当前的簇
		for (lable = 0; lable<3; lable++){
			cout << "第" << lable + 1 << "个簇：" << endl;
			vector<Tuple> t = clusters[lable];
			for (i = 0; i< t.size(); i++)
			{
				cout << "(" << t[i].attr1 << "," << t[i].attr2 << ")" << "   ";
			}
			cout << endl;
		}
	}

}
int mainvv(){

	char fname[256];
	cout << "请输入存放数据的文件名： ";
	cin >> fname;
	cout << endl;
	ifstream infile;
	infile.open(fname, ios::in);
	if (!infile){
		cout << "不能打开输入的文件" << fname << endl;
		return 0;
	}
	int count = 0;
	vector<Tuple> tuples;
	Tuple tuple;
	//从文件流中读入数据
	while (!infile.eof()){
		count++;
		if (count % 2 == 1) infile >> tuple.attr1;
		else {
			infile >> tuple.attr2;
			tuples.push_back(tuple);
		}
	}
	//int k;
	//cout<<"请输入期望的簇的个数："
	//cin>>k;
	//cout<<endl;

	//输出文件中的元组信息
	for (vector<Tuple>::size_type ix = 0; ix != tuples.size(); ++ix)
		cout << "(" << tuples[ix].attr1 << "," << tuples[ix].attr2 << ")" << "    ";
	cout << endl;
	KMeans(tuples);
	system("pause");
	return 0;

}
/*层次聚类*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
const int iniClusNum = 12;
const int stopNum = 3;

class Point
{
public:
	double x;
	double y;
	int NumPBelong;
	Point()
	{
		x = 0;
		y = 0;
		NumPBelong = -1;
	}
	Point(double x1, double y1, int f = -1) :x(x1), y(y1), NumPBelong(f){}
	const Point& operator=(const Point& p)
	{
		x = p.x;
		y = p.y;
		NumPBelong = p.NumPBelong;
		return *this;
	}
};

class ManagerP
{
public:
	double getDistance(const Point& p1, const Point& p2)
	{
		return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
	}
	Point getMean(const Point& p1, const Point& p2)
	{
		Point p;
		p.x = (p1.x + p2.x) / 2;
		p.y = (p1.y + p2.y) / 2;
		return p;
	}
};
class ManagerC
{
public:
	Point Cluster[iniClusNum];
	vector<int> ClusterLast[iniClusNum];
	bool isIndexClose[iniClusNum];
	bool isIndexClose2[iniClusNum];
	void initCluster()//use txt to init, import txt
	{
		ifstream  myfile("point.txt");
		if (!myfile)
		{
			cout << "cannot open file.";   return;
		}

		Point p;
		int x, y;
		int i = 0;
		while (!myfile.eof())
		{
			myfile >> x >> y;
			p.x = x;
			p.y = y;
			Cluster[i] = p;
			i++;
		}
		myfile.close();
	}
	void initIndexClose()
	{
		for (int i = 0; i<iniClusNum; i++)
		{
			isIndexClose[i] = false;
			isIndexClose2[i] = false;
		}
	}
	void print()
	{
		for (int i = 0; i<iniClusNum; i++)
		{
			if (ClusterLast[i].empty())
			{
				continue;
			}
			cout << "cluster " << i + 1 << endl;
			vector<int>::iterator ite = ClusterLast[i].begin();
			for (; ite != ClusterLast[i].end(); ite++)
			{
				cout << *ite << "\t";
			}
			cout << endl;

		}
		cout << endl;
	}
	void ClusterAlgo()//use minheap to realize, to optimize
	{

		int ClustNum = iniClusNum;
		int clus_index = 0;
		while (ClustNum>stopNum)
		{

			double min = INT_MAX;
			int x = -1, y = -1;
			ManagerP mp;
			for (int i = 0; i<iniClusNum; i++)
			{
				if (isIndexClose[i])
				{
					continue;
				}
				for (int j = i + 1; j<iniClusNum; j++)
				{
					if (isIndexClose[j])
					{
						continue;
					}

					double new_d = mp.getDistance(Cluster[i], Cluster[j]);
					if (new_d < min)
					{
						min = new_d;
						x = i; y = j;

					}
				}
			}
			if (x == -1 || y == -1)
			{
				break;
			}

			Point p = mp.getMean(Cluster[x], Cluster[y]);
			//x<y	store the result
			if (Cluster[x].NumPBelong == -1 && Cluster[y].NumPBelong == -1)
			{
				cout << "a0" << endl;
				ClusterLast[clus_index].push_back(x);//xchange to p, y close
				ClusterLast[clus_index].push_back(y);
				p.NumPBelong = clus_index;
				isIndexClose[y] = true;//y is closed
				Cluster[x] = p;//new p is open
				isIndexClose[x] = false;
				isIndexClose2[x] = true;
				isIndexClose2[y] = true;
				clus_index++;

			}
			else if (Cluster[x].NumPBelong == -1 && Cluster[y].NumPBelong != -1)//already exists one cluster
			{
				cout << "a1" << endl;
				ClusterLast[Cluster[y].NumPBelong].push_back(x);
				isIndexClose[x] = true;//x is closed
				p.NumPBelong = Cluster[y].NumPBelong;
				Cluster[y] = p;//new p is open
				isIndexClose2[x] = true;
			}
			else if (Cluster[x].NumPBelong != -1 && Cluster[y].NumPBelong == -1)
			{
				cout << "a2" << endl;
				ClusterLast[Cluster[x].NumPBelong].push_back(y);
				isIndexClose[y] = true;//y is closed
				p.NumPBelong = Cluster[x].NumPBelong;
				Cluster[x] = p;//new p is open
				isIndexClose2[y] = true;
			}
			else if (Cluster[x].NumPBelong != -1 && Cluster[y].NumPBelong != -1)//both are clusteroid
			{
				cout << "a3" << endl;
				vector<int>::iterator ite = ClusterLast[Cluster[y].NumPBelong].begin();//put y's node in x
				for (; ite != ClusterLast[Cluster[y].NumPBelong].end(); ite++)
				{
					ClusterLast[Cluster[x].NumPBelong].push_back(*ite);
				}
				ClusterLast[Cluster[y].NumPBelong].clear();
				isIndexClose[y] = true;//y is closed
				p.NumPBelong = Cluster[x].NumPBelong;
				Cluster[x] = p;//new p is open

			}
			ClustNum--;
		}
		int total_size = 0;
		for (int i = 0; i<stopNum; i++)
		{
			total_size += ClusterLast[i].size();
		}
		if (total_size<iniClusNum)
		{
			int j = 0;
			for (int i = 0; i<iniClusNum; i++)
			{
				if (isIndexClose2[i] == false)
				{
					ClusterLast[stopNum - 1 - j].push_back(i);
					j++;
				}
			}

		}
	}

};
int main__xx()
{
	ManagerC M;
	M.initCluster();
	M.initIndexClose();
	M.ClusterAlgo();
	M.print();
	return 0;
	system("pause");
}
