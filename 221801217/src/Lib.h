#include<iostream>
#include<string>
#include<fstream>
#include<string.h>
#include<map>
#include<algorithm>
#include<ctime>


using namespace std;

extern map<string,int> stringMap;

int countLine(string input);

int countChar(string input);

int countWord(string input);

void output(ofstream& out,string input);

int isChar(char c);

int isCharOrDig(char c);
