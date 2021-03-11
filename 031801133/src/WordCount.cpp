#include<iostream>
#include<string.h>
#include<algorithm>
#include<fstream> 
#include<map> 
#include<vector>
using namespace std;
map<string, int> m;
vector< pair<string, int> > vec;
//string input;
int countChar(string input);
int countWord(string s);
int countR(string input);
bool cmp(pair<string, int> a, pair<string, int> b) {
	if (a.second == b.second)	return a.first < b.first;
	return a.second > b.second;
}
void showWord(string input) {
	ofstream OutFile("output.txt");
	OutFile << "characters: " << countChar(input) << endl;
	OutFile << "words: " << countWord(input) << endl;
	OutFile << "lines: " << countR(input) << endl;
	for (map<string, int>::iterator it = m.begin(); it != m.end(); it++) {
		vec.push_back(pair<string, int>(it->first, it->second));
	}
	sort(vec.begin(), vec.end(), cmp);
	if (vec.size() < 10) {
		for (vector< pair<string, int> >::iterator it = vec.begin(); it != vec.end(); it++) {
			OutFile << (*it).first << ' ' << (*it).second << endl;
		}
	}
	else {
		int count = 10;
		for (vector< pair<string, int> >::iterator it = vec.begin(); it != vec.end(); it++) {
			if (count == 0)	break;
			OutFile << (*it).first << ": " << (*it).second << endl;
			count--;
		}
	}
	OutFile.close();
}
bool isWhite(char c) {
	return c == 10 || c == 13 || c == 32;
}
bool notsp(char s) {
	return (s >= 'a' && s <= 'z') || (s >= '0' && s <= '9');
}
bool isword(char s) {
	return (s >= 'a' && s <= 'z');
}
int main(int argc, char* argv[]) {
	try {
		ifstream in(argv[1], ios::in);
		istreambuf_iterator<char> beg(in), end;
		string input(beg, end);
		//cout << input<<endl;
		in.close();
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		ofstream OutFile(argv[2]);
		OutFile << "characters: " << countChar(input) << endl;
		OutFile << "words: " << countWord(input) << endl;
		OutFile << "lines: " << countR(input) << endl;
		for (map<string, int>::iterator it = m.begin(); it != m.end(); it++) {
			vec.push_back(pair<string, int>(it->first, it->second));
		}
		sort(vec.begin(), vec.end(), cmp);
		if (vec.size() < 10) {
			for (vector< pair<string, int> >::iterator it = vec.begin(); it != vec.end(); it++) {
				OutFile << (*it).first << ' ' << (*it).second << endl;
			}
		}
		else {
			int count = 10;
			for (vector< pair<string, int> >::iterator it = vec.begin(); it != vec.end(); it++) {
				if (count == 0)	break;
				OutFile << (*it).first << ": " << (*it).second << endl;
				count--;
			}
		}
		OutFile.close();
	}
	catch(exception){
		cout << "找不到文件";
	}
	return 0;
}
int countChar(string input) {
	return input.length();
}
int countWord(string input) {
	int sum = 0;
	//cout<<input<<endl;
	if (input.length() == 0)	return sum;
	for (int i = 0, j = 0;	j < input.length() && i < input.length();) {
		if (isword(input[i])) {
			//cout<<"here"<<endl;
			j = i;
			bool flag = 1;
			for (; j < i + 4; j++) {
				if (!isword(input[j])) {
					flag = 0;
					break;
				}
			}
			if (flag) {
				//sum++;
				while (notsp(input[j])) {
					j++;
				}
				if (m[input.substr(i, j - i)] == 0) {
					m[input.substr(i, j - i)]++;
					sum++;
				}
				else m[input.substr(i, j - i)]++;
				i = j + 1;
				j = i;
			}
			else {
				i = j + 1;
				j = i;
			}
		}
		else {
			if (!notsp(input[i])) {
				while (!notsp(input[i])) {
					i++;
					if (i >= input.length() - 1)
						break;
				}
			}
			else {
				while (notsp(input[i]))
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
int countR(string input) {
	int sum = 0;
	bool flag = 1;
	int i = 0;
	if (input[0] == 10) {
		while (!isWhite(input[i]))
			i++;
	}
	for (; i < input.length(); i++) {

		if ((input[i] == 10)) {
			sum++;
			while (isWhite(input[i]))
				i++;
		}
	}
	if(input.length()!=0)
		if (!isWhite(input[input.length() - 1]))
			sum++;
	return sum;
}
