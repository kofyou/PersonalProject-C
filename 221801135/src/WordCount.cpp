#include"Lib.h"

int main(int argc, char* argv[])
{
	wordCount wordcount(argv[1], argv[2]);
	wordcount.handleInPut();
	wordcount.outPut();
	return 0;
}
