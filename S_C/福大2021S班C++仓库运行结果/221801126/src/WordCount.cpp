#include "lib.h"

#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//main.cpp
int main(int argc, char* argv[]) {
    try {
    //输入
	string charString = InputFile(argv[1]);
    //转换
         transform(charString.begin(), charString.end(), charString.begin(), ::tolower);
    //输出
	OutputFlie(argv[2],charString);
     }
     catch(exception){
	cout << "error";
     }
	return 0;
}
