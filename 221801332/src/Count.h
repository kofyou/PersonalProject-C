#pragma once
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;
class Count
{
public:
	int CountCharNum(string& charBuf);
	int CountWordNum(vector<string>& linesBuf);
	int CountLineNum(vector<string>& linesBuf);
	vector<map<string, int>::iterator>& CountTop10Word();
private:
	map<string, int> WordMap;
	vector<map<string, int>::iterator> Top10Word;
	inline bool isLetter(string::iterator it);
	inline bool isLetter(const char& ch);
	inline bool isDigit(string::iterator it);
	inline bool isDigit(const char& ch);
};
