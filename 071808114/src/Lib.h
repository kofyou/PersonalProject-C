#pragma once
#pragma warning(disable:4996)
#ifndef _WORDCOUNT_H__ 
#define _WORDCOUNT_H__

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<fstream>
#include<Windows.h>
#include<string>
#include<string.h>
#include<vector>
#include<map>

using namespace std;

int CountChar(char* filein, char* fileout);//统计字符数

int CountWord(char* filein, char* fileout);//统计单词数

int CountLine(char* filein, char* fileout);//统计有效行数

void CountMaxWord(char* filein, vector<pair<string, int>>& x);//统计单词出现次数

int WriteToFile(char* fileout, vector<pair<string, int>>& x);//将单词按出现次数写入文件

//void test(char* fileout);//自动生成30000行的大文件



#endif