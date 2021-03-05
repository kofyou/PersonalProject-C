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

//逐个字符读取文件
bool FileIO::ReadChar(int argc, char *argv[],string &charBuf,vector<string> &linesBuf)
{
	string filename = FileIO::GetInputFileName(argc, argv);
	ifstream Readfile(filename);
	if (!Readfile) {
		return false;
	}
	else
	{
		string TempLine;
		char c;
		while (true)
		{
			c = Readfile.get();
			if (c == EOF)
			{
				if (TempLine.size() > 0)
				{
					transform(TempLine.begin(), TempLine.end(), TempLine.begin(), ::tolower);
					linesBuf.push_back(TempLine);
				}
				break;
			}
			if (c >= 0 && c <= 127) {
				charBuf += c;
				TempLine += c;
			}
			if (c == '\n')
			{
				transform(TempLine.begin(), TempLine.end(), TempLine.begin(), ::tolower);
				linesBuf.push_back(TempLine);
				TempLine = "";
			}
		}
		Readfile.close();
		return true;
	}
}

//输出文件
void FileIO::OutputToFile(int argc, char* argv[], int CharacterCount, int WordCount,int LineCount, vector<map<string,int>::iterator> &Top10Word)
{
	string filename = FileIO::GetOutputFileName(argc, argv);
	ofstream WriteFile(filename, ios::out);
	WriteFile << "characters: " << CharacterCount << endl;
	WriteFile << "words: " << WordCount << endl;
	WriteFile << "lines: " << LineCount << endl;
	for (int i = 0; i < int(Top10Word.size()); i++)
	{
		if (i == 0)
		{
			WriteFile  << Top10Word[i]->first <<": " << -Top10Word[i]->second;
		}
		else
		{
			WriteFile << endl << Top10Word[i]->first <<": " << -Top10Word[i]->second;
		}
	}
	WriteFile.close();
}
