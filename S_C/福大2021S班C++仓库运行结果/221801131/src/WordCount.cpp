#include<fstream> 
#include"CountWord.h"
#include <assert.h>

int main(int argv, char** argc) {
    char* input = argc[1];
    char* output = argc[2];
    if (!input)
    {
        cout << "未输入文件名或文件不存在" << endl;
        return 0;
    }
    CountWord* test = new CountWord(argc[1]);
    ofstream outfile(output, ios::out);
    if (!outfile) {
        cout << "文件打开失败！" << endl;
    }
    outfile << "characters: " << test->getcharacternum() << endl;
    outfile << "words: " << test->getwordnum1() << endl;               //单词数
    outfile << "lines: " << test->getlinenum() << endl;
    Words* wwords = test->getwords();
    for (int i = 0; i < test->getwordnum2(); i++) {
        if (i == 10)break;
        else {
            outfile << wwords[i].word;
            outfile << ": " << wwords[i].count << endl;
        }
    }
    outfile.close();
}