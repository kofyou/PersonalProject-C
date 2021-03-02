/************************************************************
 FileName: WordCount.cpp
 Author:Zou Pufan Version:7.0 Date:2021/2/27
 Description: // 模块描述
 Version: // 版本信息
 Function List: // 主要函数及其功能
 1. -------
 History: // 历史修改记录
 <author> <time> <version > <desc>
 David 96/10/12 1.0 build this moudle
***********************************************************/
#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<cstring>
#include<vector>
#include<algorithm>
#define MAX_NUM 1024

using namespace std;
class word
{
public:
	word()
	{
		this->occurCount = 0;
		this->wordName = "";
	}
	word(string wordN)
	{
		this->wordName = wordN;
		this->occurCount=1;
	}


	int occurCount;
	string wordName;
};
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
	int Countchar(fstream& in,string outputFileName);
	int Countword(fstream& in, string outputFileName);
	int Countline(fstream& in, string outputFileName);
	/*bool sortWordTimes(const word&a, const word &b);*/
	void Countwordoccurtimes(fstream& in,string outputFileName);
	
private:
	string fileName;
	int characterNum;
	int wordNum;
	vector<word> wVector;
};
/*************************************************
 Description:通过对输入的文件流进行逐字符的读取以计算字符数。
 Input: 输入参数分别为fstream类的引用in代表被打开文件的读取流，string类outputFilename代表写入输出文件的文件名// 输入参数说明，包括每个参数的作
 // 用、取值说明及参数间关系。
 Output: 输出值为输出至output文件的字符出现次数// 对输出参数的说明。
 Return:无return值 // 函数返回值的说明
 Others: // 其它说明
*************************************************/
int myfile::Countchar(fstream &in, string outputFileName)
{
	fstream out;
	out.open(outputFileName.c_str(),ios::app);
	int totalCount=0;
	char temp;
   in>>noskipws;//设置不跳过换行符和空白符
   in>>temp;
   while(!in.eof())
   {
   	totalCount++;
   	in>>temp;
   }
   out<<"characters:"<<totalCount<<'\n';
   out.close();
   out.clear();
	return totalCount;
}
/*************************************************
 Description:通过对输入的文件流进行逐行的读取，统计文件的行数
 Input: 输入参数分别为fstream类的引用in代表被打开文件的读取流，string类outputFilename代表写入输出文件的文件名// 输入参数说明，包括每个参数的作
 // 用、取值说明及参数间关系。
 Output: 输出值为输出至output文件的input文件的总共出现行数// 对输出参数的说明。
 Return:无return值 // 函数返回值的说明
 Others: // 其它说明
*************************************************/
int myfile::Countline(fstream &in, string outputFileName)
{
	fstream out;
	out.open(outputFileName.c_str(),ios::app);
	if (!in.is_open())
	{
		cout << "无法打开文件" << endl;
		exit(0);
	}
	int totalCount = 0;
	string line;
	while (!in.eof())
	{
		getline(in,line);
		for (int i = 0;i < line.length();i++)
		{
			if (!isspace(line[i]))//对文件进行逐行的读取，判断是否存在非空白字符。
			{
				totalCount++;
				break;
			}
		}
	}
	out << "line:" << totalCount << endl;
	out.close();
	out.clear();
	return totalCount;
}
