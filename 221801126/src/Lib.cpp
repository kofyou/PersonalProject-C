#include "lib.h"

using namespace std;

//InputFileMode
string InputFile(const char* filename){
	  ifstream in(filename, ios::in);
		istreambuf_iterator<char> beg(in), end;
		string sstring(beg, end);	
		in.close();		
		return sstring;
}

int CountChar(string inputString) {
	int count = 0;
	count = inputString.length();
	return count;
}


bool IsBlankChar(char c) {
	return c == LINE_FEED_NUMBER || c == CR_NUMBER || c == BLANK_SPACE_NUMBER;
}

bool NotNumberOrLetter(char s) {
//not a char like a~z or 0~9 
	return (s >= 'a' && s <= 'z') || (s >= '0' && s <= '9');
}

bool IsEnglishLetter(char s) {
	return (s >= 'a' && s <= 'z');
}

bool cmp(pair<string, int> a, pair<string, int> b) {
	if (a.second == b.second)
		return a.first < b.first;		
	else 
		return a.second > b.second;
}


