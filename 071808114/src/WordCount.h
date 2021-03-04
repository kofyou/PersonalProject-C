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

int CountChar(char* filemm);

int CountWord(char* filemm);

int CountLine(char* filemm);

void CountAndSort(char* filemm, vector<pair<string, int>>& x);

int Display(vector<pair<string, int>>& x);

#endif