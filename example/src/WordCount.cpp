#include"cir.h"
#include <iostream>

int main(int argc, char** argv)
{

	string wordcount = argv[1];

	myFile file(wordcount);
	file.get_all();
	cout << "ÒÑÊä³öÖÁout.txt" << endl;
	return 0;
}
