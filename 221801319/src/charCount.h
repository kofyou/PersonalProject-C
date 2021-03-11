#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class charCount {
    private:
		int number;
    public:
		int getNumber() {
			return number;
		}
		
		void setNumber(int number_1) {
			number = number_1;
		}
		
		void charcount(fstream &inputFile) {
			char str[256];
			int tmp = 0;
			int tmp_1 = 0;//统计换行符数目
			while (inputFile.getline(str, 256)) {
				tmp_1++;
				for (int i = 0;i < strlen(str);i++) {
					if (str[i] >= 0 && str[i] < 128) {
						tmp++;
					}
				}
			}
			setNumber(tmp+tmp_1-1);
		}
};