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

int CountWord(string inputString) {
	int sum = 0;
	
	if (inputString.length() == 0)
		return sum;
		
	for (int i = 0, j = 0;	j < inputString.length() && i < inputString.length();) {
		if (IsEnglishLetter(inputString[i])) {
			j = i;
			bool flag = 1;
			
			for ( ; j < i + POINTER_DISTANCE_NUMBER; j++) {
				if (!IsEnglishLetter(inputString[j])) {
					flag = 0;
					break;
				}
			}
			
			if (flag) {
				//sum++;
				while (NotNumberOrLetter(inputString[j])) {
					j++;
				}
				if (m[inputString.substr(i, j - i)] == 0) {
					m[inputString.substr(i, j - i)]++;
					sum++;
				}
				else m[inputString.substr(i, j - i)]++;
				i = j + 1;
				j = i;
			}
			else {
				i = j + 1;
				j = i;
			}
		}
		else {
			if (!NotNumberOrLetter(inputString[i])) {
				while (!NotNumberOrLetter(inputString[i])) {
					i++;
					if (i >= inputString.length() - 1)
						break;
				}
			}
			else {
				while (NotNumberOrLetter(inputString[i]))
					i++;
			}
		}
	}
	
	map<string, int>::iterator it = m.begin();
	while (it != m.end()) {
		if (it->second > 1) {
			sum += it->second - 1;
		}
		it++;
	}
	return sum;
}

int CountRow(string inputString) {
    int i = 0;
	int sum = 0;
	bool flag = 1;
	
	if (inputString[0] == CR_NUMBER || inputString[0] == LINE_FEED_NUMBER) {
		while (!IsBlankChar(inputString[i]))
			i++;
	}
	for (; i < inputString.length(); i++) {

		if ((inputString[i] == CR_NUMBER || inputString[i] == LINE_FEED_NUMBER)) {
			sum++;
			while (IsBlankChar(inputString[i]))
				i++;
		}
	}
	if(inputString.length()!=0)
		if (!IsBlankChar(inputString[inputString.length() - 1]))
			sum++;
	return sum;
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


