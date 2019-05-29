#include <iostream>
#include <sys/types.h> 
#include <direct.h>
#include <sys/stat.h> 
#include <windows.h>
#include <fstream>
int mainzs()
{
	int count = 0;
	HANDLE hFile;
	LPCTSTR lpFileName = "F:/work/E200Code/VisionApp/build/demo/sample/Template/*";
	WIN32_FIND_DATA pNextInfo;
	hFile = FindFirstFile(lpFileName, &pNextInfo);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::cout << "direction open failed" << std::endl;
		return -1;
	}
	std::ofstream file;
	file.open("F:\\work\\E200Code\\VisionApp\\build\\demo\\sample\\Template\\filename.txt",std::ios::out);
	if (!file.is_open())
	{
		std::cout << "file open failed" << std::endl;
	}
	while (FindNextFile(hFile, &pNextInfo))
	{
		count++;
		if (pNextInfo.cFileName[0] == '.')
		{
			count--;
			continue;
		}
		file << pNextInfo.cFileName << std::endl;
		std::cout << "第" << count << "文件名为：" << pNextInfo.cFileName << std::endl;
	}
	file.close();
	system("pause");

	return 0;
}
