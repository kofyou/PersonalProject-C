

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<regex>
#include<map>
#include<algorithm>
#include"Count.h"
#include"FileIO.h"
using namespace std;

int main(int argc, char *argv[] ) 
{
	int LineCount = 0;
	int CharacterCount = 0;
	int WordCount = 0;
	Count count;
	string charBuf;
	vector<string> linesBuf;

	if(FileIO::ReadChar(argc, argv, charBuf, linesBuf))			
	{
		CharacterCount = count.CountCharNum(charBuf);
		LineCount = count.CountLineNum(linesBuf);
		WordCount = count.CountWordNum(linesBuf);
		vector<map<string, int>::iterator> Top10Word = count.CountTop10Word();
		FileIO::OutputToFile(argc, argv, CharacterCount, WordCount, LineCount, Top10Word);
	}
	else
	{
		cout << "read file faliure";
	}
	return 0;
}
