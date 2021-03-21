#include "Lib.h"


map<string, int> stringMap;//统计词频



int main(int argc, char** argv) {
	ifstream in;
	in.open(argv[1]);
	istreambuf_iterator<char> beg(in),end;
	string input(beg,end);
	transform(input.begin(),input.end(),input.begin(),::tolower);
//	cout<<input<<endl;
	in.close();
	
	ofstream out;
	out.open(argv[2]);
	output(out,input);
	out.close();
	
	return 0;
}
