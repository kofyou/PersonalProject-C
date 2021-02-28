#include<fstream> 
#include<WordCount.h>

int main(int argv, char** argc) {
    char* input = argc[1];
    char* output = argc[2];
    WordCount* test = new WordCount(argc[1]);
    ofstream outfile(output, ios::out);
    outfile << "characters:" << test->getcharacternum() << endl;      //字符数
    outfile << "words:" << test->getwordnum1() << endl;               //单词数
    outfile << "lines:" << test->getlinenum() << endl;                //行数
    Words* wwords = test->getwords();
    for (int i = 0; i < test->getwordnum2(); i++) {
        if (i == 10)break;
        else {
            outfile << wwords[i].word;
            outfile << ":" << wwords[i].count << endl;
        }
    }
    outfile.close();
}