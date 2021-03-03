#include "WordCount.h"

int main(int argc, char** argv)
{
	ifstream inFile;
	inFile.open("F:\\test.txt");
	char buffer[MAXWORDS] = {};
	int i = 0;
	char x;
	while ((x=inFile.get())!=EOF)
	{
		buffer[i] = x;
		i++;
	}
	cout << GetLines(buffer);
}