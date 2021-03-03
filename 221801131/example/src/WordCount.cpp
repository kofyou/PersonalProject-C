#include"WordCount.h"
using namespace std;

typedef pair<string, int> PAIR;

struct CmpByValue {
    bool operator()(const PAIR& lhs, const PAIR& rhs) {
        if (lhs.second == rhs.second) {//词频相同时
            if (lhs.first.compare(rhs.first) > 0)return false;
            else return true;
        }
        else return lhs.second > rhs.second;
    }
};

WordCount::WordCount() {
    wordnum2 = 0;
    characternum = 0;
    wordnum1 = 0;
    linenum = 0;
    wwords = new Words[wordnum2];
}

WordCount::WordCount(char* Path) {
    wordnum2 = 0;
    characternum = charactersCount(Path);
    wordnum1 = wordCount(Path);
    linenum = lineCount(Path);
    wwords = new Words[wordnum2];
    wordsort();
}

int WordCount::getcharacternum() {
    return characternum;
}
int WordCount::getlinenum() {
    return linenum;
}
int WordCount::getwordnum1() {
    return wordnum1;
}

int WordCount::getwordnum2() {
    return wordnum2;
}

Words* WordCount::getwords() {
    return wwords;
}

int WordCount::charactersCount(char* Path) {    //计算字符数量
    ifstream infile(Path, std::ios::binary);    //二进制读解决读不到'\r'的问题
    if (!infile) {
        cout << "文件打开失败！" << endl;
    }
    char code;
    int num = 0;
    infile >> noskipws;//强制读入空格和换行符
    while (!infile.eof())
    {
        infile >> code;
        if (infile.eof())
            break;//防止最后一个字符输出两次
        num++;
    }
    infile.close();
    return num;
}

int WordCount::wordCount(char* Path) {    //计算单词个数
    ifstream infile(Path);
    if (!infile) {
        cout << "文件打开失败！" << endl;
    }
    char word;
    char* str = new char[100];  //记录单词
    bool flag = false;
    bool isWords = false;
    int charCount = 0;//记录字母数
    int num = 0;
    word = infile.get();
    while (true) {
        if (word >= 'A' && word <= 'Z')word += 32;
        if (flag)
        {
            if (!((word >= 'a' && word <= 'z') || (word >= '0' && word <= '9'))) { //确认一个单词后寻找下一个间隔符
                if (isWords) {
                    str[charCount] = NULL;
                    safeWord(str);
                }
                memset(str, NULL, sizeof(str));
                flag = false;
                isWords = false;
                charCount = 0;
            }
            else if (isWords) {
                str[charCount++] = word;
            }
        }
        else {
            if (word >= 'a' && word <= 'z') {    //判断是否是字母
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

int WordCount::lineCount(char* Path) {    //计算行
    ifstream infile(Path, std::ios::binary);
    if (!infile) {
        cout << "文件打开失败！" << endl;
    }
    char code;
    bool flag = false;
    int num = 0; 
    infile >> noskipws;
    while (!infile.eof()) {
        while(infile >> code) {
            if (code >= 0 && code <= 127) {
                if (!isspace(code))
                    flag = true;
            }
            if (code == '\r' || code == '\n')
                break;
        }
        if (flag){
            num++;
            flag = false;
        }
    }
    infile.close();
    return num;
}

void WordCount::safeWord(char* str) {
    string word;
    word = str;
    map<string, int>::iterator iter = words.find(word);//找单词 
    if (iter == words.end()) {
        words.insert(pair<string, int>(word, 1));//没找到单词，插入单词并设定次数为1 
        wordnum2++;                              //单词个数+1
    }
    else {
        iter->second++;//找到单词，单词出现次数增加 
    }
}

void WordCount::wordsort() {//词频排序
	Words temp;
    map<string, int>::iterator iter;
    vector<PAIR> vwords(words.begin(), words.end());
    sort(vwords.begin(), vwords.end(), CmpByValue());
    for (int i = 0; i != vwords.size(); ++i) {
        wwords[i].word = vwords[i].first;
        wwords[i].count = vwords[i].second;
    }
}