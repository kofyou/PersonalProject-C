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
#include <regex>
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
    void judgeWord(char*);
    Words* getsW();

private:
    int chars;
    int words;
    int lines;
    int sums;
    map<string, int> wordSet;
    Words* pwords;
};

int analysisFlie::getChars()
{
    return chars;
}
int analysisFlie::getSums()
{
    return sums;
}

map<string, int> mapword1;

Words* analysisFlie::getsW()
{
    return pwords;
}

analysisFlie analysisFlie::countChar(char* a, analysisFlie b) //计算字符数
{
    int i = 0;
    ifstream file1;
    file1.open(a, std::ios::out | std::ios::binary); //以二进制读取不会漏读\t等
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
        {
            break;
        }
        i++;
    }
    b.chars = i;
    file1.close();
    return b;
}

typedef pair<string, int> PAIR;

bool cmp_by_value(const PAIR& lhs, const PAIR& rhs)
{
    return lhs.second > rhs.second;
}

struct CmpByValue
{
    bool operator()(const PAIR& lhs, const PAIR& rhs)
    {
        return lhs.second > rhs.second;
    }
};

char changeChar(char a) //大写转小写
{
    if (a >= 'A' && a <= 'Z')
        a += 32;
    return a;

}

int isChar(char a) //判断是否是字符范围内
{
    return ((a >= 48 && a <= 57) || (a >= 97 && a <= 122));

}

int analysisFlie::getLines()
{
    return lines;
}

int analysisFlie::getWords()
{
    return words;
}

void analysisFlie::init() //初始化
{
    chars = 0;
    words = 0;
    lines = 0;
    sums = 0;
    text = (char*)malloc(sizeof(char*) * 1000000);
}

void load(char w[])   //用map存取单词
{
    string a;
    a = w;
    map<string, int>::iterator iter = mapword1.find(a);
    if (iter == mapword1.end())
        mapword1.insert(pair<string, int>(a, 1));
    else
        ++iter->second;
}

analysisFlie analysisFlie::countLine(char* a, analysisFlie b) //计算行数
{
    int i = 0;
    ifstream file1;
    file1 >> noskipws;
    file1.open(a, std::ios::binary);  //以二进制打开
    if (!file1.is_open())
    {
        cout << "File open failed" << endl;
    }
    string d;
    while (!file1.eof())
    {
        getline(file1, d);  //一行一行读
        if (file1.eof())
        {
            break;
        }
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


analysisFlie analysisFlie::countWord(char* a, analysisFlie b) //计算单词
{
    int n = 0;
    ifstream file1;
    file1.open(a);
    if (!file1.is_open())
    {
        cout << "File open failed" << endl;
    }
    char word1;
    char* str = new char[100];
    int sym = false;
    int isWord = false;
    int charCount = 0;
    word1 = file1.get();
    file1 >> noskipws;
    while (!file1.eof())//将大写统一转换成小写
    {
        file1 >> word1;
        if (file1.eof())
            break;
        word1 = changeChar(word1);
        b.text[n++] = word1;
    }
    file1.close();
    char store[4] = { 0 };
    int i = 0;
    int j = 0;
    int m = 0;
    int k = 0;
    for (i = 0; i < n; i++)
    {
        if (!isChar(b.text[i])) //如果不属于0-9及a-z跳过继续循环
            continue;
        else
        {
            for (j = 0; j < 4 && i < n; j++) //计算存储合适的字符串
            {
                if (!isChar(b.text[i]))
                    break;
                store[j] = b.text[i++];
            }
            if (j == 4)
            {
                for (m = 0; m < 4; m++) //如果不是字母开头则不符合要求
                {
                    if (store[m] < 97 || store[m]>122)
                    {
                        sym = 1;
                        break;
                    }
                }
                if (sym == 0) //符合要求的话将单词存入w，再存入map
                {
                    char* w = new char[1000];
                    b.sums++;
                    for (m = 0; m < 4; m++)
                    {
                        w[k++] = store[m];
                    }
                    while (isChar(b.text[i]) && i < n)
                    {
                        w[k++] = b.text[i++];
                    }
                    w[k] = '\0';
                    load(w);
                    isWord++;
                    delete[]w;
                    k = 0;
                }
                else
                {
                    sym = 0;
                    j = 0;
                }
            }
        }
    }
    b.words = isWord;
    return b;
}

void merge(Words* a, Words* b, int left, int mid, int right) //归并排序
{
    int i = left, j = mid + 1, m = 1;
    while (i <= mid && j <= right) 
    {
        if (a[i].count < a[j].count) b[m++] = a[j++];
        else b[m++] = a[i++];
    }
    while (i <= mid) b[m++] = a[i++];
    while (j <= right) b[m++] = a[j++];
    for (int n = 1; n <= right - left + 1; n++)
        a[left + n - 1] = b[n];
}

void sort(Words* a, Words* b, int left, int right) 
{ //归并排序
    if (left < right) 
    {
        int mid = (left + right) / 2;
        sort(a, b, left, mid);
        sort(a, b, mid + 1, right);
        merge(a, b, left, mid, right);
    }
}

void analysisFlie::judgeWord(char* a) //其实没有用到这个函数
{ 
    string word;
    word = a;
    map<string, int>::iterator iter = wordSet.find(word);
    if (iter == wordSet.end()) 
    {
        wordSet.insert(pair<string, int>(word, 1));
        sums++;
    }
    else 
    {
        iter->second++;
    }
}

void analysisFlie::wordSort() 
{ 
    Words temp;
    map<string, int>::iterator iter;
    iter = wordSet.begin();
    int count = 0;
    for (; iter != wordSet.end(); iter++, count++) 
    {
        pwords[count].word = iter->first;
        pwords[count].count = iter->second;
    }
    vector<PAIR> word1(wordSet.begin(), wordSet.end());
    sort(word1.begin(), word1.end(), CmpByValue());
    for (int i = 0; i != word1.size(); ++i) {
        pwords[i].word = word1[i].first;
        pwords[i].count = word1[i].second;
    }
}