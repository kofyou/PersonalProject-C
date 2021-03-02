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
/*************************************************
 Description:通过对输入的文件流进行逐字符的读取，将读取到的字符拼接为字符串，在遇到分割符后将先前拼接成的字符串进行检查，判断是否为有效的单词，若有效则加入vector集合中。无效则跳过。
 Input: 输入参数分别为fstream类的引用in代表被打开文件的读取流，string类outputFilename代表写入输出文件的文件名// 输入参数说明，包括每个参数的作
 // 用、取值说明及参数间关系。
 Output: 输出值为输出至output文件的单词总计出现次数// 对输出参数的说明。
 Return:无return值 // 函数返回值的说明
 Others: // 其它说明
*************************************************/
int myfile::Countword(fstream &in, string outputFileName)
{
	bool isWord = true;//判断字符串内容是否符合单词组成
	fstream out;
	out.open(outputFileName.c_str(),ios::app);
	in.unsetf(ios_base::skipws);//设置不跳过换行符和空白符
	if (!in.is_open())
	{
		cout << "无法打开文件" << endl;
		exit(0);
	}
	int totalCount = 0;
	string wordString = "";
	char temp;
    in>>noskipws;
    if(in.eof())
    {
   	cout<<"文件到达末尾"<<endl;
    }
    while(!in.eof())
    {

   	in>>temp;
	if (temp <= 'Z'&&temp >= 'A')//如果字符为大写字母将其转换为小写字母
	{
		temp += 32;
	}
	if (temp <= 32 || temp>126||temp=='\n')//判断是否遇到分割符，是则执行以下条件
	{
		if (wordString.length() < 4)//如果单词长度小于4，则直接跳过并清除字符串内容
		{
			wordString = "";
			continue;
		}
		for (int i = 0;i < 4;i++)
		{
			if (!isalpha(wordString[i]))//判断字符串前四位是否为字母，不为字母则直接结束循环
			{
				wordString = "";
				isWord = false;
				break;
			}

		}
		if (!isWord)//如果不为单词则继续执行下一个while循环，不执行以下代码
		{
			isWord = true;
			continue;
		}
		totalCount++;

		//通过find_if函数外加自定义的findword函数判断单词是否在vector容器中出现过，若出现过则添加单词次数即可，未出现过则加入新的元素。
		vector<word>::iterator it = find_if(this->wVector.begin(), this->wVector.end(), findword(wordString));
		if (it != this->wVector.end())
		{
			it->occurCount++;
		}
		else
		{
			this->wVector.push_back(word(wordString));
			
		}
		wordString = "";
	}
	else	wordString=wordString+temp;
    }
    if (!wordString.empty())//当文件读取结束后没有遇到分隔符却字符串中却仍有内容，要进行最后一次检查。
    {
	   if (wordString.length() < 4)
	   {
		   wordString = "";
		  
	   }
	   for (int i = 0;i <= 4;i++)
	   {
		   if (!isalpha(wordString[i]))
		   {
			   wordString = "";
			   isWord = false;
			   break;
		   }

	   }
	   if (isWord)
	   {
		   for (int j = 0;j < wordString.length();j++)
		   {

			   if (wordString[j] <= 'Z'&&wordString[j] >= 'A')
			   {
				   wordString[j] += 32;
			   }
		   }
		   totalCount++;
		   vector<word>::iterator it = find_if(this->wVector.begin(), this->wVector.end(), findword(wordString));
		   if (it != this->wVector.end())
		   {
			   it->occurCount++;

		   }
		   else
		   {
			   this->wVector.push_back(word(wordString));

		   }
		   wordString = "";
	   }
	   else
	   {
		   isWord = true;
	   }
    }
    in.close(); 
    in.clear();
    out << "word:" << totalCount << endl;//输出单词的数量
    out.close();
    out.clear();
 	return totalCount;
}
