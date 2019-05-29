#include <iostream>
#include <windows.h>
#if  0
int main30(int argc, char *argv[])
{
	WIN32_FIND_DATA dataofFile;
	HANDLE opshandle;
	printf("Target file is %s./n", argv[1]);
	opshandle = FindFirstFile(argv[1], &dataofFile);
	if (INVALID_HANDLE_VALUE == opshandle)
	{
		printf("file  invalid");
	}
	else{

		printf("the first file found is %s", dataofFile.cFileName);
	}

	system("pause");
	return 0;
}
#endif 