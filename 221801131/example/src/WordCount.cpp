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
    ifstream infile(Path);
    if (!infile) {
        cout << "文件打开失败！" << endl;
    }
    char code;
    int num = 0;
    /*while ((code = infile.get()) != EOF) {   //这两个有不知道的问题
        if (code >= 0 && code <= 127)num++;
    }*/
    /*string str;
    while (getline(infile, str)) //以行为单位读入文件
        num += str.size(); //累计字符数
     */
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
                //cout << str << endl;
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
    ifstream infile(Path);
    if (!infile) {
        cout << "文件打开失败！" << endl;
    }
    string line;
    int num = 0;
    while (!infile.eof()) {
        getline(infile, line);
        int i = 0;
        while (i < line.length() && isspace(line[i])){
            i++;
        }
        if (i != line.length()){
            num++;
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

void WordCount::wordsort() {
	Words temp;
    map<string, int>::iterator iter;
    iter = words.begin();
    int count = 0;
    for (; iter != words.end(); iter++, count++) {
        wwords[count].word = iter->first;
        wwords[count].count = iter->second;
    }
    /*for (int i = 0; i < count; i++) {                              //冒泡排序
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
    }*/
    vector<PAIR> vwords(words.begin(), words.end());
    sort(vwords.begin(), vwords.end(), CmpByValue());
    //sort(vwords.begin(), vwords.end(), cmp_by_value);
    for (int i = 0; i != vwords.size(); ++i) {
        wwords[i].word = vwords[i].first;
        wwords[i].count = vwords[i].second;
    }
}