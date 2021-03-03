#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iomanip>
//#include "WordCount.h"
using namespace std;

struct Word
{
    int frequency = 1;
    string word;
};

vector<Word> words;
Word oneWord;

void countCharacter(char*, char*);
void countLine(char*, char*);
void countWord(char*, char*);
void sortWord(char*);
bool isExist(string);
bool isWord(string);
string convertToLower(string);

bool operator<(Word& w1, Word& w2)
{
    if (w1.frequency == w2.frequency)
    {
        return w1.word < w2.word;
    }
    else
        return w1.frequency > w2.frequency;
}


int main(int argc, char* argv[])
{
    char* inFile = argv[1];
    char* outFile = argv[2];

    countCharacter(inFile, outFile);
    countWord(inFile, outFile);
    countLine(inFile, outFile);
    sortWord(outFile);
    //int num_i = atoi(argv[i]); 
    return 0;
}

void countCharacter(char* inFile, char* outFile)
{
    fstream fin(inFile, ios::in);
    if (!fin.is_open())
    {
        cout << "以读方式打开文件失败" << endl;
        exit(0);
    }
    char ch;
    int chNumber = 0;
    while (fin.get(ch))
    {
        if ((ch >= 32 && ch <= 126) || ch == 9 || ch == 10 || ch == 13)
        {
            chNumber++;
        }
    }
    fin.close();

    fstream fout(outFile, ios::out);
    if (!fout.is_open())
    {
        cout << "以写方式打开文件失败!" << endl;
        exit(0);
    }
    //cout << chNumber << endl;
    fout << "characters: " << chNumber - 1 << '\n';//chNumber的结果要消除BOM的影响
    fout.close();
}

void countWord(char* inFile, char* outFile)
{
    fstream fin(inFile, ios::in);
    if (!fin.is_open())
    {
        cout << "以读方式打开文件失败!" << endl;
        exit(0);
    }

    char ch;
    bool judge = false;
    string word = "";
    int wordNumber = 0;
    while (fin.get(ch))
    {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
        {
            word += ch;
        }
        else
        {
            judge = isWord(word);
            if (judge)
            {
                //cout << word << endl;
                word = convertToLower(word);

                if (!isExist(word))
                {
                    oneWord.word = word;
                    words.push_back(oneWord);
                }

                wordNumber++;
                judge = false;
            }
            word = "";
        }
    }
    fin.close();

    fstream fout(outFile, ios::app);
    if (!fout.is_open())
    {
        cout << "以写方式打开文件失败!" << endl;
        exit(0);
    }
    fout << "words: " << wordNumber << '\n';
    fout.close();
}

void countLine(char* inFile, char* outFile)
{
    fstream fin(inFile, ios::in);
    if (!fin.is_open())
    {
        cout << "以读方式打开文件失败!" << endl;
        exit(0);
    }
    char ch;
    int judge = 0;//判断一行中是否有非空白符
    int lineNumber = 0;
    while (fin.get(ch))
    {
        if (ch == 10)
        {
            if (judge)
                lineNumber++;
            judge = 0;
        }
        if (ch >= 33 && ch <= 126) judge = 1;
    }
    fin.close();

    fstream fout(outFile, ios::app);
    if (!fout.is_open())
    {
        cout << "以写方式打开文件失败!" << endl;
        exit(0);
    }
    fout << "lines: " << lineNumber << '\n';
    fout.close();
}

//对统计好的单词进行排序
void sortWord(char* outFile)
{
    sort(words.begin(), words.end());
    fstream fout(outFile, ios::app);
    if (!fout.is_open())
    {
        cout << "以写方式打开文件失败!" << endl;
        exit(0);
    }
    vector<Word>::iterator it;
    int i;
    for (i = 0, it = words.begin();(it != words.end()) && i < 10;it++, i++)
    {
        fout << (*it).word << ": " << (*it).frequency << '\n';
    }
    fout.close();
}


bool isWord(string str)
{
    if (str.length() < 4)
        return false;
    for (int i = 0;i < 4;i++)
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'));
        else
            return false;
    }
    return true;
}

//判断单词是否被计算过
bool isExist(string str)
{
    vector<Word>::iterator it;
    for (it = words.begin();it != words.end();it++)
    {
        if (str == ((*it).word))
        {
            (*it).frequency++;
            return true;
        }
    }
    return false;
}

string convertToLower(string str)
{
    for (int i = 0;i < str.length();i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] += 32;
        }
    }
    return str;
}
