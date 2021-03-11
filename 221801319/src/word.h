#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class my_word {
	private:
		string str;//printf("%s",str.c_str())
		int freque=0;
	public:
		my_word() {
			str = ' ';
		}
		void setStr(string str_) {
			str = str_;
		}
		string getStr() {
			return str;
		}
		void addFreque() {
			freque++;
		}
		int getFreque() {
			return freque;
		}
};
