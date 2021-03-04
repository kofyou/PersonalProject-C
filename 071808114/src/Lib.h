#pragma once
#ifndef _WORDCOUNT_H__ 
#define _WORDCOUNT_H__

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<fstream>
#include<string>
#include<string.h>
#include<vector>
#include<map>

using namespace std;

int CountChar(char* filein, char* fileout);//统计字符数

int CountWord(char* filein, char* fileout);//统计单词数

int CountLine(char* filein, char* fileout);//统计有效行数

int CountMaxWord(char* filein, char* fileout, vector<pair<string, int>>& x);//统计单词出现次数


#endif