#include<iostream>
#include <fstream> 
#include <map> 
using namespace std;

int charactersCount(char* Path);
int wordCount(char* Path);
int lineCount(char* Path);
void safeWord(char* str);

map<string, int> words;//用于存放单词及次数
struct Words           //用于存放单词及次数
{
    string word;
    int count;
};

int main(int argv, char** argc) {
    char* input = argc[1];
    char* output = argc[2];
    int count = 0;
    ofstream outfile(output, ios::out);
    count = charactersCount(input);
    outfile << "characters:" << count << endl;
    count = wordCount(input);
    outfile << "words:" << count << endl;               //单词数
    Words* wwords = new Words[count];                       //分配大小为单词数目的空间 
    Words temp;
    map<string, int>::iterator iter;
    iter = words.begin();
    for (count = 0; iter != words.end(); iter++, count++) {
        wwords[count].word = iter->first;
        wwords[count].count = iter->second;
    }
    for (int i = 0; i < count; i++) {                              //冒泡排序
        for (int j = 0; j < count - i - 1; j++) {
            if (wwords[j].count < wwords[j + 1].count) {
                temp = wwords[j];
                wwords[j] = wwords[j + 1];
                wwords[j + 1] = temp;
            }
            else if (wwords[j].count == wwords[j + 1].count) {
                if (!wwords[j].word.compare(wwords[j + 1].word)) { //频率相同的单词，优先输出字典序靠前的单词。
                    temp = wwords[j];
                    wwords[j] = wwords[j + 1];
                    wwords[j + 1] = temp;
                }
            }
        }
    }
    int wordnum = count;//这里记录单词个数，不是总数
    count = lineCount(input);
    outfile << "lines:" << count << endl;
    for (int i = 0; i < wordnum; i++) {
        if (i == 10)break;
        else {
            outfile << wwords[i].word;
            outfile << ":" << wwords[i].count << endl;
        }
    }



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
    char* str = new char[100];  //记录单词
    bool flag = false;
    bool isWords = false;
    int charCount = 0;//记录字母数
    int num = 0;
    word = infile.get();
    while (true) {
        if (flag)
        {
            if (!((word >= 'a' && word <= 'z') || (word >= 'A' && word <= 'Z') || (word >= '0' && word <= '9'))) { //确认一个单词后寻找下一个间隔符
                //cout << str << endl;
                if (isWords) {
                    str[charCount] = NULL;
                    safeWord(str);
                }
                memset(str, 0, sizeof(str));
                flag = false;
                isWords = false;
                charCount = 0;
            }
            else if (isWords) {
                str[charCount++] = word;
            }
        }
        else {
            if ((word >= 'a' && word <= 'z') || (word >= 'A' && word <= 'Z')) {    //判断是否是字母
                str[charCount++] = word;
                if (charCount == 4) {     //4个英文字母开头时计一个单词数并寻找下一个间隔符
                    num++;
                    flag = true;
                    isWords = true;
                }
            }
            else {                    //没有4个英文字母开头则寻找下一个间隔符
                flag = true;
                continue;
            }
        }
        if ((word = infile.get()) == EOF)break;
    }
    if (isWords) {                   //若最后一个为单词则保存
        str[charCount] = NULL;
        safeWord(str);
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

void safeWord(char* str) {
    string word;
    word = str;
    map<string, int>::iterator iter = words.find(word);//找单词 
    if (iter == words.end()) {
        words.insert(pair<string, int>(word, 1));//没找到单词，插入单词并设定次数为1 
    }
    else {
        iter->second++;//找到单词，单词出现次数增加 
    }
}