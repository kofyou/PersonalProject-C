#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class wordCount {
private:
	int number;
public:
	int getNumber() {
		return number;
	}

	void setNumber(int number_1) {
		number = number_1;
	}

	void wordcount(fstream &inputFile) {
		//string str;
		char data[256];
		int tmp = 0;
		int tmp_1 = 0;//统计单词开头字母个数
		bool flag = true;//标志分隔符
		while (inputFile.getline(data,256) ){
			for (int i = 0;i < strlen(data);i++) {
				if (isalpha(data[i])) {
					data[i]=tolower(data[i]);
				}//全部转换为小写
				if ((data[i] >= 'a' && data[i] <= 'z') || (data[i] >= 'A' && data[i] <= 'Z')) {
					if (flag) {
						tmp_1++;
					}
				}
				else if ((data[i] >= '0' && data[i] <= '9')&&tmp_1 < 4) {
					tmp_1 = 0;
					flag = false;
				}
				else if (!((data[i] >= 'a' && data[i] <= 'z') ||/* (data[i] >= 'A' && data[i] <= 'Z') ||*/ (data[i] >= '0' && data[i] <= '9'))) {
					flag = true;
					if (tmp_1 < 4) {
						tmp_1 = 0;
					}
					else {
						tmp_1 = 0;
						tmp++;
					}
				}
			}
			if (tmp_1 >= 4) {
				tmp++;
				tmp_1 = 0;
			}
		}
		setNumber(tmp);
	}
};