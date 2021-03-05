#pragma once
#include<iostream>
#include<stdio.h>
#include<string>
#include<map>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;

class FileIO
{
public:
	static bool ReadChar(int argc, char *argv[], string &CharBuf,vector<string> &LinesBuf);
	static void OutputToFile(int argc, char* argv[], int CharacterCount, int LineCount, int WordCount, vector<map<string,int>::iterator> &Top10Word);
private:
	static string GetInputFileName(int argc, char *argv[]);
	static string GetOutputFileName(int argc, char* argv[]);

};
