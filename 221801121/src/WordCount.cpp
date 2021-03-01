#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cassert>
#include <string>
#include <cstdlib>
#include <malloc.h>
using namespace std;

struct Words
{
    string word;
    int count;
};

class analysisFlie
{
public:
    analysisFlie countChar(char*, analysisFlie);
    analysisFlie countWord(char*, analysisFlie);
    analysisFlie countLine(char*, analysisFlie);
    int getChars();
    int getWords();
    int getLines();
    int getSums();
    char* text;
    void init();
    void wordSort();
    void judgeWord( char *);


private:
    int chars;
    int words;
    int lines;
    int sums;
    map<string, int> wordSet;
    Words * pwords;
};

int analysisFlie::getChars()
{
    return chars;
}
analysisFlie analysisFlie::countChar(char *a, analysisFlie b)
{
    int i = 0;
    ifstream file1;
    file1.open(a);
    if (!file1.is_open())
    {
        cout << "File open failed" << endl;
    }
    char c;
    file1 >> noskipws;
    while (!file1.eof())
    {
        file1 >> c;
        if (file1.eof())
            break;
        i++;
    }
    b.chars = i;
    file1.close();
    return b;
}

int analysisFlie::getLines()
{
    return lines;
}
int analysisFlie::getWords()
{
    return words;
}

void analysisFlie::judgeWord(char* a) {
    string word;
    word = a;
    map<string, int>::iterator iter = wordSet.find(word);
    if (iter == wordSet.end()) {
        wordSet.insert(pair<string, int>(word, 1));
        sums++;  
    }
    else {
        iter->second++;
    }
}

void analysisFlie::init()
{
    chars = 0;
    words = 0;
    lines = 0;
    text = (char *)malloc(sizeof(char *) * 1000000);
}

analysisFlie analysisFlie::countLine(char *a, analysisFlie b)
{
    int i = 1;
    ifstream file1;
    file1.open(a);
    if (!file1.is_open())
    {
        cout << "File open failed" << endl;
    }
    char c;
    string d;
    while (!file1.eof())
    {
        getline(file1, d);
        if (file1.eof())
            break;
        if (d.empty())
        {
            i--;
        }

        i++;
    }
    b.lines = i;
    file1.close();
    return b;
}

analysisFlie analysisFlie::countWord(char* a, analysisFlie b)
{
    int i = 0;
    ifstream file1;
    file1.open(a);
    if (!file1.is_open())
    {
        cout << "File open failed" << endl;
    }
    char word1;
    char* str = new char[100]; 
    bool flag = false;
    bool isWord = false;
    int charCount = 0;
    word1 = file1.get();
    while (true) 
    {
        word1 = changeChar(word1);
        if (flag)
        {
            if (!((word1 >= 'a' && word1 <= 'z') || (word1 >= '0' && word1 <= '9'))) {
                if (isWord) {
                    str[charCount] = NULL;
                    judgeWord(str);
                }
                memset(str, NULL, sizeof(str));
                flag = false;
                isWord = false;
                charCount = 0;
            }
            else if (isWord) {
                str[charCount++] = word1;
            }
        }
        else {
            if (word1 >= 'a' && word1 <= 'z') {
                str[charCount++] = word1;
                if (charCount == 4) { 
                    i++;
                    flag = true;
                    isWord = true;
                }
            }
            else {
                flag = true;
                continue;
            }
        }
        if ((word1 = file1.get()) == EOF)break;
    }
    if (isWord) {
        str[charCount] = NULL;
        judgeWord(str);
    }
    b.words = i;
    file1.close();
    return b;
}

int main(int argc, char* argv[])
{
    int i;
    int j;
    int num;
    analysisFlie file1;
    file1.init();
    if (!argv[1])
    {
        cout << "未输入文件名或文件不存在" << endl;
        return 0;
    }
    file1 = file1.countChar(argv[1], file1);
    file1 = file1.countLine(argv[1], file1);
    file1 = file1.countWord(argv[1], file1);
    ofstream file2;
    file2.open("AAA.txt");
    file2 << "character:" << file1.getChars() << endl;
    file2 << "line:" << file1.getLines() << endl;
    file2 << "words:" << file1.getWords() << endl;
}
