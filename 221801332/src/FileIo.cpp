#include "FileIO.h"

//获取文件名
string FileIO::GetInputFileName(int argc, char *argv[])
{
	if (argc == 2 || argc == 3)
	{
		return string(argv[1]);
	}
	else
	{
		cout << "文件格式错误，将用默认文件input.txt" << endl;
		return "input.txt";
	}
}

string FileIO::GetOutputFileName(int argc, char* argv[])
{
	if (argc == 3)
	{
		return string(argv[2]);
	}
	else
	{
		return "result.txt";
	}
}
