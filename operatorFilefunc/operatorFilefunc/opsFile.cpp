#include <iostream>
#include <windows.h>

int main01(int argc, char *argv[])
{
	//char *path = "E:\\";
	//char *lpFileName = "E:\\*.jpg";
	using namespace std;
//#ifdef debug
	WIN32_FIND_DATA dataofFile;
	HANDLE opshandle;
	printf("Target file is %s.\n", argv[1]);
	opshandle = FindFirstFileA(argv[1], &dataofFile);
	if (INVALID_HANDLE_VALUE == opshandle)
	{
		printf("file  invalid");
	}
	else{

		printf("the first file found is %s\n", dataofFile.cFileName);
		std::cout << "the attributes of file is  " << dataofFile.dwFileAttributes << std::endl;
		std::cout << "the file created time is  " << dataofFile.ftCreationTime.dwHighDateTime << "  and  " << dataofFile.ftCreationTime.dwLowDateTime<< std::endl;
		std::cout << "the attributes of file is  " << dataofFile.dwFileAttributes << std::endl;
		std::cout << "the last wirote of file is  " << dataofFile.ftLastWriteTime.dwHighDateTime << "  and  " << dataofFile.ftLastWriteTime .dwLowDateTime<< std::endl;

	}
	while (FindNextFileA(opshandle, &dataofFile))
	{
		if (opshandle == INVALID_HANDLE_VALUE)
		{
			std::cout << "count found next file" << std::endl;
		}
		else{
			printf("the nextt file found is---> %s\n", dataofFile.cFileName);
			std::cout << "the attributes of file is--->  " << dataofFile.dwFileAttributes << std::endl;
			std::cout << "the file created time is--->  " << dataofFile.ftCreationTime.dwHighDateTime << "  and  " << dataofFile.ftCreationTime.dwLowDateTime << std::endl;
			std::cout << "the attributes of file is--->  " << dataofFile.dwFileAttributes << std::endl;
			std::cout << "the last wirote of file is--->  " << dataofFile.ftLastWriteTime.dwHighDateTime << "  and  " << dataofFile.ftLastWriteTime.dwLowDateTime << std::endl;
		}
	}
	
#if 0
	HANDLE hFile;
	LPCTSTR lpFileName = "E:\\*.*";	//ָ������Ŀ¼���ļ����ͣ�������d�̵���Ƶ�ļ�������"D:\\*.mp3"
	WIN32_FIND_DATA pNextInfo;	//�����õ����ļ���Ϣ��������pNextInfo��;
	hFile = FindFirstFile(lpFileName, &pNextInfo);//��ע���� &pNextInfo , ���� pNextInfo;
	if (hFile == INVALID_HANDLE_VALUE)
	{
		//����ʧ��
		exit(-1);
	}
	while (FindNextFile(hFile, &pNextInfo))
	{
		if (pNextInfo.cFileName[0] == '.')//����.��..
			continue;
		cout << "�õ��ļ���" << pNextInfo.cFileName << endl;
	}
#endif
	system("pause");
	return 0;
}