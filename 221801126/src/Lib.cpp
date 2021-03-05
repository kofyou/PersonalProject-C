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
