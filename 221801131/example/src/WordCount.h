#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Words //用于存放单词及次数
{
    string word;
    int count;
};

class WordCount
{
private:
    int characternum;
    int wordnum1; //单词总数
    int wordnum2; //单词个数
    int linenum;
    map<string, int> words; //用于存放单词及次数
    Words *wwords;

public:
    WordCount(char *Path);
    int getcharacternum();
    int getlinenum();
    int getwordnum1();
    int getwordnum2();
    Words *getwords();
    int charactersCount(char *Path);
    int wordCount(char *Path);
    int lineCount(char *Path);
    void safeWord(char *str);
    void wordsort();
};