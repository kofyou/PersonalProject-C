#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class rowCount {
private:
	int number;
public:
	int getNumber() {
		return number;
	}

	void setNumber(int number_1) {
		number = number_1;
	}

	void rowcount(fstream& inputFile) {
		string str;
		int tmp = 0;
		while (getline(inputFile,str)) {
			int len = str.length();
			for (int i = 0;i < len;i++) {
				if (str[i] != ' ') {
					tmp++;
					break;
				}
			}
		}
		setNumber(tmp);
	}
};
