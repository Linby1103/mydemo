/*
有1元、5元、10元、50元、100元、500元的硬币各C1, C5, C10, C50, C100, C500枚。
现在要用这些硬币来支付Pay_x元，最少需要多少枚硬币？若有解，输出最少硬币数；
否则输出“-1”（0<=C1, C5, C10, C50, C100, C500<=10^9，0<=A<=10^9）
分析：用最大面额的硬币来支付，则需要的硬币数量应该最少
规划：局部最优解：面额最大的硬币数量，全局最优解：最少的硬币数量
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <stdlib.h>
#define Max(a,b)    (((a) > (b)) ? (a) : (b))
#define Min(a,b)    (((a) < (b)) ? (a) : (b))
#define MAX_SIZE 6
using namespace std;
const int  moneyVal[MAX_SIZE] = { 1, 5, 10, 50, 100, 500 };//硬币的面值
int moneynum[MAX_SIZE] = {0};//每种面值硬币的数量
int Sum = 0;
int ret[MAX_SIZE] = { 0 }/*每种硬币使用的 个数*/;
int main(int argc, char *argv[])
{
	int Pay_x = 0, num = 0;//
	cout << "请输入需要支付的金额!" << endl;
	cout << ": ";    cin >> Pay_x;

	cout << "请输入你拥有每种硬币的个数：" << endl;
	for (int i = 0; i < MAX_SIZE; ++i)
	{ 
		//int _moneynum = 0;
		cout << ": ";	cin >> moneynum[i];

		cout << "面值为 " << moneyVal[i] << " 元的硬币有 " << moneynum[i] << " 枚" << endl;
	}
	cout << endl;
	for (int j = MAX_SIZE - 1; j >= 0; --j)
	{
		/*temp记录使用硬币j的枚数,其值<=moneyVal[j]*/
		int temp = (Pay_x / moneyVal[j]);
		num=Min(temp, moneynum[j]);
		/*Pay_x剩余未支付的硬币*/
		Pay_x -= num*moneyVal[j];
		/*记录第j中面值的硬币使用的个数*/
		ret[j] = num;
		/*记录总共使用的硬币的个数*/
		Sum += num;
	}
	if (Pay_x > 0)
	{
		cout << "所有的硬币不足以支付需要支付的金额！" << endl;
	}
	cout << "所需最少的硬币数量为:" << num << " 枚" << endl;
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		cout << "面值为 " << moneyVal[i] << " 的硬币使用了 " << ret[i] << " 枚" << endl;
	}
	system("pause");
	return 0;
}

/*
“背包”相关问题
 （Ⅰ）最优装载问题
有n个物体，第i个物体的重量为wi（wi为正整数）。选择尽量多的物体，使得总重量不超过C。
【分析】由于只关心选择的物品的最大数量（而不是最大重量，最大重量需要考虑DP），所以装重的物体没有装轻的物体划算。
这里只需对n个物体按重量递增排序，依次选择每个物体直到装不下为止。
规划:
局部最优：最轻的背包数量
全局最优：装载数量最多
*/
#define STR_SIZE 50
typedef struct backpacker{
public:
	float Total_Wght;/*能容纳的最大重量*/
	//vector<int> count;
	//char goods_name[];
	map<char*, int> goods_Info;
}backpack, *Pkt;
backpack pck;
int main0(int argc, char *argv[])
{
	Pkt pBke = &pck;
	char   goodsname[STR_SIZE];
	int    goodsnum = 0;
	cout << "请输入背包的能容纳的最大重量：" << endl;
	cout << ": "; cin >> pBke->Total_Wght;
	cout << "请输入物品的名称和数量,以q结束输入" << endl;
	
	while (true)
	{
		cout << "\n :";
		getchar();
		cin.getline(goodsname, STR_SIZE); cout << "    "; cin >> goodsnum;
		if (goodsname[0] == 'q')
			break;
		pBke->goods_Info.insert(pair<char*, int>((char*)&goodsname, goodsnum));
	}


	return 0;
}