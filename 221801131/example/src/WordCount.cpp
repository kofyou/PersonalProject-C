#include<iostream>
#include <fstream> 
using namespace std;

int charactersCount(char* Path);
int wordCount(char* Path);
int lineCount(char* Path);

int main(int argv, char** argc) {
    char* input = argc[1];
    char* output = argc[2];
    int count = 0;
    count = charactersCount(input);
    ofstream outfile(output, ios::out);
    outfile << "characters:" << count << endl;
    count = wordCount(input);
    outfile << "words:" << count << endl;               //单词数
    count = lineCount(input);
    outfile << "lines:" << count << endl;


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

int wordCount(char* Path) {    //计算单词个数
    ifstream infile(Path);
    char word;
    int charCount = 0;//记录字母数
    int num = 0;
    bool flag = false;
    while ((word = infile.get()) != EOF) {
        if (flag)
        {
            if (!((word >= 'a' && word <= 'z') || (word >= 'A' && word <= 'Z') || (word >= '0' && word <= '9'))) { //确认一个单词后寻找下一个间隔符
                flag = false;
                charCount = 0;
            }
        }
        else {
            if ((word >= 'a' && word <= 'z') || (word >= 'A' && word <= 'Z')) {    //判断是否是字母
                charCount++;
                if (charCount == 4) {     //4个英文字母开头时计一个单词数并寻找下一个间隔符
                    num++;
                    flag = true;
                }
            }
            else {                    //没有4个英文字母开头则寻找下一个间隔符
                flag = true;
            }
        }
    }
    infile.close();
    return num;
}


int lineCount(char* Path) {    //计算行
    ifstream infile(Path);
    char line[255];
    int num = 0;
    while (infile) {
        infile.getline(line, 255);
        if (strlen(line) != 0)num++;
    }
    infile.close();
    return num;
}