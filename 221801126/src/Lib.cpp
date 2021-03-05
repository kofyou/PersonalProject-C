#include "lib.h"

using namespace std;

map<string, int> m;
vector< pair<string, int> > vec;
//////////////////////////////////

void OutputFlie(char* filename,string inputString) {
	//
	ofstream outputFlie(filename);
	
	outputFlie << "characters: " << CountChar(inputString) << endl;
	outputFlie << "words: " << CountWord(inputString) << endl;
	outputFlie << "lines: " << CountRow(inputString) << endl;
	
	for (map<string, int>::iterator it = m.begin(); it != m.end(); it++) {
		vec.push_back(pair<string, int>(it->first, it->second));
	}
	//sort  
	sort(vec.begin(), vec.end(), cmp);
	if (vec.size() < MAX_OUTPUT_NUMBER) {
		for (vector< pair<string, int> >::iterator it = vec.begin(); it != vec.end(); it++) {
			outputFlie << (*it).first << ' ' << (*it).second << endl;
		}
	}
	else {
	int outPutNum = MAX_OUTPUT_NUMBER;
			for (vector< pair<string, int> >::iterator it = vec.begin(); it != vec.end(), outPutNum > 0; it++) {
				outputFlie << (*it).first << ": " << (*it).second << endl;
				outPutNum--;
			}
	}
	outputFlie.close();
}

string InputFile(const char* filename){//输入 
	    ifstream in(filename, ios::in);
		istreambuf_iterator<char> beg(in), end;
		string sstring(beg, end);	
		in.close();		
		return sstring;
}
//////////////////////////////// 

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
	
	if (inputString[0] == '\t' || inputString[0] == '\r'|| inputString[0] == '\n') {
		while (!IsBlankChar(inputString[i]))
			i++;
	}
	for (; i < inputString.length(); i++) {

		if ((inputString[i] == '\t' || inputString[i] == '\r'|| inputString[i] == '\n')) {
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
//////////////////////////////////////////////// 

bool IsBlankChar(char c) {
	return c == '\r' || c == ' '||c == '\n'|| c == '\t';
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
