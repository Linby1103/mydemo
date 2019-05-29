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


int APIENTRY WinMain(HINSTANCE hInstance, //应用程序的实例句柄，
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine, //命令行
	int       nCmdShow) //显示方式
{
	MSG msg;
	HWND hWnd;
	char szTitle[] = "系统信息";        // The title bar text
	char szWindowClass[] = "popMsg";        // The title bar text
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);  //WNDCLASSEX结构体大小
	wcex.style = CS_HREDRAW | CS_VREDRAW; //位置改变时重绘
	wcex.lpfnWndProc = (WNDPROC)WndProc;   //消息处理函数
	wcex.hInstance = 0;   //当前实例句柄
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOWFRAME; //背景色
	wcex.lpszClassName = szWindowClass;  //参窗口类名
	wcex.hIcon = 0;  //图标
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);  //光标
	wcex.lpszMenuName = 0;  //菜单名称
	wcex.hIconSm = 0;  //最小化图标
	RegisterClassEx(&wcex);   //注册窗口类

	hWnd = CreateWindow(szWindowClass, szTitle, WS_SYSMENU | WS_VISIBLE, //创建窗口
		CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, 0, NULL);
	if (!hWnd){
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))  // 消息循环:
	{
		TranslateMessage(&msg);  //转化虚拟按键到字符消息
		DispatchMessage(&msg);  //分派消息调用回调函数
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
	case WM_PAINT:  //重绘消息
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
	case WM_DESTROY: //窗口销毁消息
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
/*窗口视图讯息处理程序:

视窗讯息处理程式确定了在视窗
的显示区域中显示些什么以及视窗怎样回应使用者输入。
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;

	static char* thisAppName = "hello windows";
	switch (message)
	{
	case WM_PAINT:  //重绘消息
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);/*得到的是相对于窗口客户区左上角的坐标。*/
		MoveToEx(hdc, 10, 10, 0);/*移动当前画笔的位置*/
		SelectObject(hdc, ::CreatePen(PS_SOLID, 1, RGB(0, 0, 255)));/*把一个对象(位图、画笔、画刷等)选入指定的设备描述表。新的对象代替同一类型的老对象。*/
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
	case WM_DESTROY: //窗口销毁消息
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

}

int APIENTRY WinMain(HINSTANCE hInstance, //应用程序的实例句柄，
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine, //命令行
	int       nCmdShow)
{

	
	/*1.0初始化结构*/

	WNDCLASSEX wcex = { 0 };/*实验表明必须初始化，负责窗口视图注册会失败*/
	HWND HandleWNd;
	MSG _msg;
	static char thisAppName[] = "hello windows";
	char szWindowClass[] = "winclass";
	char szTitle[] = "系统信息";
	wcex.cbSize = sizeof(WNDCLASSEX);  //WNDCLASSEX结构体大小
	wcex.style = CS_HREDRAW | CS_VREDRAW; //位置改变时重绘
	wcex.lpfnWndProc = (WNDPROC)WndProc;   //消息处理函数
	wcex.hInstance = 0;   //当前实例句柄
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOWFRAME; //背景色
	wcex.lpszClassName = szWindowClass;  //参窗口类名
	wcex.hIcon = 0;  //图标
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);  //光标
	wcex.lpszMenuName = 0;  //菜单名称
	wcex.hIconSm = 0;  //最小化图标

	/*2.0注册窗口视图*/
	RegisterClassEx(&wcex);
	//{
	//	//MessageBox(/*HandleWNd*/NULL, TEXT("This program requires Windows NT!"),
	//		//thisAppName, MB_ICONERROR);
	//		
	//}
	/*3.0创建窗口视图*/
	HandleWNd = CreateWindow(szWindowClass, szTitle, WS_SYSMENU | WS_VISIBLE, //创建窗口
		CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, 0, NULL);
		//CreateWindow(szWindowClass, szTitle, WS_SYSMENU | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, 0, NULL);
	/*显示窗口视图*/
	//ShowWindow(HandleWNd, nCmdShow);
	ShowWindow(HandleWNd, nCmdShow);
	/*更新窗口视图*/
	UpdateWindow(HandleWNd);
	/*讯息回圈*/
	/*程式现在必须准备
      读入使用者用键盘和滑鼠输入的资料。Windows 为当前执行的每个Windows 程式
      维护一个「讯息伫列」。在发生输入事件之後，Windows 将事件转换为一个「讯
      息」并将讯息放入程式的讯息伫列中。
	  GetMessage:
	  这一呼叫传给Windows 一个指标，指向名为msg 的MSG 结构。第二、第三
	  和第四个参数设定为NULL 或者0，表示程式接收它自己建立的所有视窗的所有
	  讯息
	  */
	while (GetMessage(&_msg, NULL, 0, 0))  // 消息循环:
	{
		TranslateMessage(&_msg);  //将msg 结构传给Windows，进行一些键盘转换  转化虚拟按键到字符消息
		DispatchMessage(&_msg);  // 又将msg 结构回传给Windows   ,分派消息调用回调函数
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
	//spInt栈对象结束生命期，随之析构堆对象Int(10)，同时释放内存资源
}

void main()
{
	SmartPtAuto_ptr();
	system("pause");
}

//执行结果如下:
/*
Constructor: 10
PrintValue: 10
PrintValue: 20
PrintValue: 30
Destructor: 30
*/