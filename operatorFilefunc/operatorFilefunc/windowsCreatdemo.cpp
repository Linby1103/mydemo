#include <iostream>
//#include <Windows.h>
//void registerMyWndclass(HINSTANCE hInstance);
//LRESULT CALLBACK winProc(HWND hWnd,UINT msg,WPARAM wParam, LPARAM lParam);
//
//int APIENTRY WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd )
//{
// registerMyWndclass(hInstance);
// HWND hWnd=CreateWindow("YW","mywindow",WS_OVERLAPPEDWINDOW,100,100,640,480,NULL,NULL,hInstance,NULL);
// if(hWnd)
// {
//  ShowWindow(hWnd,SW_NORMAL);
//  UpdateWindow(hWnd);
// }
// MSG msg;
// while(GetMessage(&msg,NULL,0,0))
// {
//  TranslateMessage(&msg);
//  DispatchMessage(&msg);
// }
// return 0;
//}
//void registerMyWndclass(HINSTANCE hInstance)
//{
// WNDCLASSEX* wc=new WNDCLASSEX;
// wc->cbClsExtra=NULL;
// wc->cbSize=sizeof(WNDCLASSEX);
// wc->cbWndExtra=NULL;
// wc->hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
// wc->hCursor=LoadCursor(NULL,IDC_ARROW);
// wc->hIcon=LoadIcon(NULL,IDI_WINLOGO);
// wc->hIconSm=NULL;
// wc->hInstance=hInstance;
// wc->lpfnWndProc=winProc;
// wc->lpszMenuName=NULL;
// wc->lpszClassName="MYWINDOW";
// wc->style=CS_HREDRAW |CS_VREDRAW;
// RegisterClassEx(wc);
//}
//LRESULT CALLBACK winProc(HWND hWnd,UINT msg,WPARAM wParam, LPARAM lParam)
//{
// switch(msg)
// {
// case WM_DESTROY:
//  PostQuitMessage(0);
//  return 0;
//  ///...more case statement
//
// default:
//  break;
// }
// return  DefWindowProc(hWnd,msg,wParam,lParam);
//}

//#include "stdafx.h"

#include <windows.h>
#define operatorWinShow
#ifdef operatorFileDebug

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY WinMain(HINSTANCE hInstance, //Ӧ�ó����ʵ�������
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine, //������
	int       nCmdShow) //��ʾ��ʽ
{
	MSG msg;
	HWND hWnd;
	char szTitle[] = "ϵͳ��Ϣ";        // The title bar text
	char szWindowClass[] = "popMsg";        // The title bar text
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);  //WNDCLASSEX�ṹ���С
	wcex.style = CS_HREDRAW | CS_VREDRAW; //λ�øı�ʱ�ػ�
	wcex.lpfnWndProc = (WNDPROC)WndProc;   //��Ϣ������
	wcex.hInstance = 0;   //��ǰʵ�����
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOWFRAME; //����ɫ
	wcex.lpszClassName = szWindowClass;  //�δ�������
	wcex.hIcon = 0;  //ͼ��
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);  //���
	wcex.lpszMenuName = 0;  //�˵�����
	wcex.hIconSm = 0;  //��С��ͼ��
	RegisterClassEx(&wcex);   //ע�ᴰ����

	hWnd = CreateWindow(szWindowClass, szTitle, WS_SYSMENU | WS_VISIBLE, //��������
		CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, 0, NULL);
	if (!hWnd){
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))  // ��Ϣѭ��:
	{
		TranslateMessage(&msg);  //ת�����ⰴ�����ַ���Ϣ
		DispatchMessage(&msg);  //������Ϣ���ûص�����
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	switch (message)
	{
	case WM_PAINT:  //�ػ���Ϣ
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		MoveToEx(hdc, 10, 10, 0);
		SelectObject(hdc, ::CreatePen(PS_SOLID, 1, RGB(0, 0, 255)));
		LineTo(hdc, 300, 200);
		Rectangle(hdc, 150, 150, 400, 400);
		//   DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
		EndPaint(hWnd, &ps);
		break;

	case WM_CREATE:

		RegisterHotKey(hWnd, 1, 0, 0x41);
		break;
	case WM_HOTKEY:
		MessageBox(0, 0, 0, 0);
		break;
	case WM_TIMER:


		break;
	case WM_DESTROY: //����������Ϣ
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
#else
#if 0
/*typedef LRESULT (CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);*/
/*������ͼѶϢ�������:

�Ӵ�ѶϢ�����ʽȷ�������Ӵ�
����ʾ��������ʾЩʲô�Լ��Ӵ�������Ӧʹ�������롣
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;

	static char* thisAppName = "hello windows";
	switch (message)
	{
	case WM_PAINT:  //�ػ���Ϣ
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);/*�õ���������ڴ��ڿͻ������Ͻǵ����ꡣ*/
		MoveToEx(hdc, 10, 10, 0);/*�ƶ���ǰ���ʵ�λ��*/
		SelectObject(hdc, ::CreatePen(PS_SOLID, 1, RGB(0, 0, 255)));/*��һ������(λͼ�����ʡ���ˢ��)ѡ��ָ�����豸�������µĶ������ͬһ���͵��϶���*/
		LineTo(hdc, 300, 200);
		Rectangle(hdc, 150, 150, 400, 400);
		//   DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
		EndPaint(hWnd, &ps);
		break;

	case WM_CREATE:

		RegisterHotKey(hWnd, 1, 0, 0x41);
		break;
	case WM_HOTKEY:
		MessageBox(hWnd, TEXT("This is WM_HOTKEY"), 0, 0);/*MessageBox(HandleWNd, TEXT("This program requires Windows NT!"),
			thisAppName, MB_ICONERROR);*/
		break;
	case WM_TIMER:


		break;
	case WM_DESTROY: //����������Ϣ
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

}

int APIENTRY WinMain(HINSTANCE hInstance, //Ӧ�ó����ʵ�������
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine, //������
	int       nCmdShow)
{

	
	/*1.0��ʼ���ṹ*/

	WNDCLASSEX wcex = { 0 };/*ʵ����������ʼ�������𴰿���ͼע���ʧ��*/
	HWND HandleWNd;
	MSG _msg;
	static char thisAppName[] = "hello windows";
	char szWindowClass[] = "winclass";
	char szTitle[] = "ϵͳ��Ϣ";
	wcex.cbSize = sizeof(WNDCLASSEX);  //WNDCLASSEX�ṹ���С
	wcex.style = CS_HREDRAW | CS_VREDRAW; //λ�øı�ʱ�ػ�
	wcex.lpfnWndProc = (WNDPROC)WndProc;   //��Ϣ������
	wcex.hInstance = 0;   //��ǰʵ�����
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOWFRAME; //����ɫ
	wcex.lpszClassName = szWindowClass;  //�δ�������
	wcex.hIcon = 0;  //ͼ��
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);  //���
	wcex.lpszMenuName = 0;  //�˵�����
	wcex.hIconSm = 0;  //��С��ͼ��

	/*2.0ע�ᴰ����ͼ*/
	RegisterClassEx(&wcex);
	//{
	//	//MessageBox(/*HandleWNd*/NULL, TEXT("This program requires Windows NT!"),
	//		//thisAppName, MB_ICONERROR);
	//		
	//}
	/*3.0����������ͼ*/
	HandleWNd = CreateWindow(szWindowClass, szTitle, WS_SYSMENU | WS_VISIBLE, //��������
		CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, 0, NULL);
		//CreateWindow(szWindowClass, szTitle, WS_SYSMENU | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, 0, NULL);
	/*��ʾ������ͼ*/
	//ShowWindow(HandleWNd, nCmdShow);
	ShowWindow(HandleWNd, nCmdShow);
	/*���´�����ͼ*/
	UpdateWindow(HandleWNd);
	/*ѶϢ��Ȧ*/
	/*��ʽ���ڱ���׼��
      ����ʹ�����ü��̺ͻ�����������ϡ�Windows Ϊ��ǰִ�е�ÿ��Windows ��ʽ
      ά��һ����ѶϢ���С����ڷ��������¼�֮�ᣬWindows ���¼�ת��Ϊһ����Ѷ
      Ϣ������ѶϢ�����ʽ��ѶϢ�����С�
	  GetMessage:
	  ��һ���д���Windows һ��ָ�ָ꣬����Ϊmsg ��MSG �ṹ���ڶ�������
	  �͵��ĸ������趨ΪNULL ����0����ʾ��ʽ�������Լ������������Ӵ�������
	  ѶϢ
	  */
	while (GetMessage(&_msg, NULL, 0, 0))  // ��Ϣѭ��:
	{
		TranslateMessage(&_msg);  //��msg �ṹ����Windows������һЩ����ת��  ת�����ⰴ�����ַ���Ϣ
		DispatchMessage(&_msg);  // �ֽ�msg �ṹ�ش���Windows   ,������Ϣ���ûص�����
	}
	
	return _msg.wParam;


}

#endif
#endif
#include<iostream>
#include<memory>
using namespace std;

class Int
{
public:
	Int(int nValue = 0)
	{
		m_nValue = nValue;
		std::cout << "Constructor: " << m_nValue << std::endl;
	}
	~Int()
	{
		std::cout << "Destructor: " << m_nValue << std::endl;
	}
	void PrintValue()
	{
		std::cout << "PrintValue: " << m_nValue << std::endl;
	}
	void SetValue(int nSetValue)
	{
		m_nValue = nSetValue;
	}

private:
	int m_nValue;
};
void SmartPtAuto_ptr()
{
	std::auto_ptr<Int > Intops(new Int(0));
	Intops->SetValue (100000);
	Intops->PrintValue();
	//spIntջ������������ڣ���֮�����Ѷ���Int(10)��ͬʱ�ͷ��ڴ���Դ
}

void main()
{
	SmartPtAuto_ptr();
	system("pause");
}

//ִ�н������:
/*
Constructor: 10
PrintValue: 10
PrintValue: 20
PrintValue: 30
Destructor: 30
*/