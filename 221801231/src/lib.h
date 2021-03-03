#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
#include <direct.h>
using namespace std;
class myfile
{
public:
	myfile()
	{
		this->fileName = "";
		this->characterNum = this->wordNum = 0;
	}
	myfile(string s)
	{
		this->fileName = s;
		this->characterNum = this->wordNum = 0;
	}
	int Countchar(fstream& in, fstream &out);
	int Countword(fstream& in, fstream &out);
	int Countline(fstream& in, fstream &out);
	void Sortmap(fstream &out);
	string fileName;
	int characterNum;
	int wordNum;
	map<string, int> wMap;
};