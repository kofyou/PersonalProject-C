#include"Lib.h"

int main(int argc, char* argv[])
{
	if (argc == 3)
	{
		wordCount wordcount(argv[1], argv[2]);
		wordcount.handleInPut();
		wordcount.outPutAll();
	}
	else
	{
		string inFileName;
		string outFileName;
		cin >> inFileName >> outFileName;
		wordCount wordcount(inFileName, outFileName);
		wordcount.handleInPut();
		wordcount.outPutAll();
	}
	
	return 0;
}
