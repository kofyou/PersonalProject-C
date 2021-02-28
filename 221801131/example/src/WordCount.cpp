#include<iostream>
#include <fstream> 
using namespace std;

int charactersCount(char* Path);

int main(int argv, char** argc) {
    char* input = argc[1];
    char* output = argc[2];
    int count = 0;
    count = charactersCount(input);
    ofstream outfile(output, ios::out);
    outfile << "characters:" << count << endl;


    outfile.close();
}

int charactersCount(char* Path) {    //计算字符数量
    ifstream infile(Path);
    char code;
    int num = 0;
    while ((code = infile.get()) != EOF) {
        if (code >= 0 && code <= 127)num++;
    }
    infile.close();
    return num;
}