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

int countCharacter(char*);
int countLine(char*);
int countWord(char*);
void sortWord();
void printResult(char*, int, int, int);
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
    int chNumber = 0;
    int wordNumber = 0;
    int lineNumber = 0;

    chNumber = countCharacter(inFile);
    wordNumber = countWord(inFile);
    lineNumber = countLine(inFile);
    sortWord();
    printResult(outFile, chNumber, lineNumber, wordNumber);
    return 0;
}

void printResult(char* outFile, int chNumber, int lineNumber, int wordNumber)
{
    fstream fout(outFile, ios::out);
    if (!fout.is_open())
    {
        cout << "以写方式打开文件失败!" << endl;
        exit(0);
    }
    fout << "characters: " << chNumber - 1 << '\n';//chNumber的结果要消除BOM的影响
    fout << "words: " << wordNumber << '\n';
    fout << "lines: " << lineNumber << '\n';

    vector<Word>::iterator it;
    int i;
    for (i = 0, it = words.begin();(it != words.end()) && i < 10;it++, i++)
    {
        fout << i + 1 << '.' << (*it).word << ": " << (*it).frequency << '\n';
    }

    fout.close();
}

int countCharacter(char* inFile)
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
    return chNumber;
}

int countWord(char* inFile)
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

    return wordNumber;
}

int countLine(char* inFile)
{
    fstream fin(inFile, ios::in);
    if (!fin.is_open())
    {
        cout << "以读方式打开文件失败!" << endl;
        exit(0);
    }
    char ch;
    int judge = 0;//用于判断一行中是否有非空白符
    int lineNumber = 0;
    while (fin.get(ch))
    {
        if (ch == 10)
        {
            if (judge)
                lineNumber++;
            judge = 0;
        }
        if (ch >= 33 && ch <= 126)
            judge = 1;
    }
    fin.close();

    return lineNumber;
}

//对统计好的单词进行排序
void sortWord()
{
    sort(words.begin(), words.end());
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
