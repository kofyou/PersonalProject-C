#include "Lib.h"


map<string, int> stringMap;//Í³¼Æ´ÊÆµ



int main(int argc, char** argv) {
	ifstream in;
	in.open(argv[1]);
	istreambuf_iterator<char> beg(in), end;
	string input(beg, end);
//	cout << input<<endl;
	in.close();
	
	
	ofstream out;
	out.open(argv[2]);
	ouput(out);
	out.close();
	
	
	return 0;
}
