/*
��1Ԫ��5Ԫ��10Ԫ��50Ԫ��100Ԫ��500Ԫ��Ӳ�Ҹ�C1, C5, C10, C50, C100, C500ö��
����Ҫ����ЩӲ����֧��Pay_xԪ��������Ҫ����öӲ�ң����н⣬�������Ӳ������
���������-1����0<=C1, C5, C10, C50, C100, C500<=10^9��0<=A<=10^9��
���������������Ӳ����֧��������Ҫ��Ӳ������Ӧ������
�滮���ֲ����Ž⣺�������Ӳ��������ȫ�����Ž⣺���ٵ�Ӳ������
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
const int  moneyVal[MAX_SIZE] = { 1, 5, 10, 50, 100, 500 };//Ӳ�ҵ���ֵ
int moneynum[MAX_SIZE] = {0};//ÿ����ֵӲ�ҵ�����
int Sum = 0;
int ret[MAX_SIZE] = { 0 }/*ÿ��Ӳ��ʹ�õ� ����*/;
int main(int argc, char *argv[])
{
	int Pay_x = 0, num = 0;//
	cout << "��������Ҫ֧���Ľ��!" << endl;
	cout << ": ";    cin >> Pay_x;

	cout << "��������ӵ��ÿ��Ӳ�ҵĸ�����" << endl;
	for (int i = 0; i < MAX_SIZE; ++i)
	{ 
		//int _moneynum = 0;
		cout << ": ";	cin >> moneynum[i];

		cout << "��ֵΪ " << moneyVal[i] << " Ԫ��Ӳ���� " << moneynum[i] << " ö" << endl;
	}
	cout << endl;
	for (int j = MAX_SIZE - 1; j >= 0; --j)
	{
		/*temp��¼ʹ��Ӳ��j��ö��,��ֵ<=moneyVal[j]*/
		int temp = (Pay_x / moneyVal[j]);
		num=Min(temp, moneynum[j]);
		/*Pay_xʣ��δ֧����Ӳ��*/
		Pay_x -= num*moneyVal[j];
		/*��¼��j����ֵ��Ӳ��ʹ�õĸ���*/
		ret[j] = num;
		/*��¼�ܹ�ʹ�õ�Ӳ�ҵĸ���*/
		Sum += num;
	}
	if (Pay_x > 0)
	{
		cout << "���е�Ӳ�Ҳ�����֧����Ҫ֧���Ľ�" << endl;
	}
	cout << "�������ٵ�Ӳ������Ϊ:" << num << " ö" << endl;
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		cout << "��ֵΪ " << moneyVal[i] << " ��Ӳ��ʹ���� " << ret[i] << " ö" << endl;
	}
	system("pause");
	return 0;
}

/*
���������������
 ��������װ������
��n�����壬��i�����������Ϊwi��wiΪ����������ѡ����������壬ʹ��������������C��
������������ֻ����ѡ�����Ʒ�����������������������������������Ҫ����DP��������װ�ص�����û��װ������廮�㡣
����ֻ���n�����尴����������������ѡ��ÿ������ֱ��װ����Ϊֹ��
�滮:
�ֲ����ţ�����ı�������
ȫ�����ţ�װ���������
*/
#define STR_SIZE 50
typedef struct backpacker{
public:
	float Total_Wght;/*�����ɵ��������*/
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
	cout << "�����뱳���������ɵ����������" << endl;
	cout << ": "; cin >> pBke->Total_Wght;
	cout << "��������Ʒ�����ƺ�����,��q��������" << endl;
	
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