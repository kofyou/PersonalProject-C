#pragma  once

#define POINTER_DISTANCE_NUMBER 4 //pointer distance between 1to2 is four
#define BLANK_SPACE_NUMBER 32 //blankspace ' '
#define LINE_FEED_NUMBER 10 //linefeed
#define T_NUMBER 9 // \t
#define CR_NUMBER 13 //enter \r
#define MAX_OUTPUT_NUMBER 10 //output max to 10

#include<iostream>
#include<string.h>
#include<fstream> 
#include<map> 
#include<vector>
#include<algorithm>
using namespace std;

string InputFile(const char* filename);
void OutputFlie(char* filename,string inputString) ;

int CountChar(string inputString);
int CountWord(string inputString);
int CountRow(string inputString);

bool cmp(pair<string, int> a, pair<string, int> b);
bool IsBlankChar(char c);
bool NotNumberOrLetter(char s);
bool IsEnglishLetter(char s);

extern map<string, int> m;
extern vector< pair<string, int> > vec;
