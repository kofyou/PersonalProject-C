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
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
#include <direct.h>
#include "./lib.h"
#include "./lib.cpp"
#define MAX_NUM 1024

using namespace std;
int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "参数输入错误";
	}
	string inputFileName = "";
	string outputFileName = "";
	inputFileName = argv[1];
	outputFileName = argv[2];
	myfile* mf = new myfile(inputFileName);

	fstream in;
	fstream out;
	string openInputFileName="./"+inputFileName;
	string openOutputFileName="./"+outputFileName;
	in.open(openInputFileName.c_str(), ios::binary| ios_base::in);
	if (!in.is_open())
	{
		cout << "无法打开文件:"<<argv[1] << endl;
		exit(0);
	}
	out.open(openOutputFileName.c_str(), ios::out);
	out.close();
	out.clear();
	out.open(openOutputFileName.c_str(), ios::app);
	mf->Countchar(in,out);
	in.close();
	in.clear();
	in.open(openInputFileName.c_str());
	mf->Countword(in,out);
	in.close();
	in.clear();
	in.open(openInputFileName.c_str());
	mf->Countline(in,out);
	in.close();
	in.clear();
	in.open(openInputFileName.c_str());
	mf->Sortmap(out);
	in.close();
	in.clear();
	out.close();
	out.clear();
}
