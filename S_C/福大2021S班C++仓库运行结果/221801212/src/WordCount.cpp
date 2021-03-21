#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
string duan = "";
int wordcount = 0;
int line = 1;
int character = 0;
struct Record
{
    string word;
    int count;
};
static bool sortType(const Record& v1, const Record& v2)
{
    return v1.count > v2.count;//降序排序
}
int wordTest(char a)
{
    return ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'));
}
void lineCount(const char* filename)//行数统计 
{
    ifstream ifile(filename);
    if (!ifile.good())
    {
        cout << "输入文件打开失败" << endl;
        return;
    }
    vector<char> para;
    int i = 0;
    char wordd;
    while ((wordd = ifile.get()) != EOF)
    {
        para.push_back(wordd);
        i++;
    }
    para.push_back('\0');
    para.push_back('\0');
    for (i = 0; i < para.size(); i++)
    {
        if (para[i] == '\n') {
            line++;
        }
    }
}
void wordCount(const char* filename)//单词统计
{
    ifstream ifile(filename);
    if (!ifile.good())
    {
        cout << "输入文件打开失败" << endl;
        return;
    }
    vector<char> para;
    int i = 0;
    int j = 0;
    char wordd;
    while ((wordd = ifile.get()) != EOF)
    {
        para.push_back(wordd);
        i++;
    }
    para.push_back('\0');
    para.push_back('\0');
    //for (int f = 0; f < para.size(); f++)
    //{
    //    cout << para[f];
    //}
    //cout << endl << i << "  " << para.size();
    i = 0;
    while (para[i] != '\0')
    {
        while (wordTest(para[i]))
        {
            i++;
            j++;
            if (!wordTest(para[i]))
            {
                if (j >= 4)
                {
                    wordcount++;
                    for (int h = i - j; h < i; h++)
                    {
                        duan = duan + para[h];
                    }
                    duan += " ";
                }
                j = 0;
            }
        }
        i++;
    }
    ifile.close();
}
void characterCount(const char* filename)//字符数量统计
{
    ifstream ifile(filename);
    if (!ifile.good())
    {
        cout << "输入文件打开失败" << endl;
        return;
    }
    char chara;
    while ((chara = ifile.get()) != EOF)
    {
        character++;
    }
}
void wordDis()//运行框测试展示
{
    vector<Record> _words;
    istringstream iss(duan);
    string word;
    int i;
    while (iss >> word)
    {
        for (i = 0; i < _words.size(); ++i)
        {
            if (word == _words[i].word)
            {
                ++_words[i].count;
                break;
            }
        }
        if (i == _words.size())
        {
            Record record;
            record.word = word;
            record.count = 1;
            _words.push_back(record);
        }
    }
    cout << duan << endl;
    cout << "字符数：" << character << endl;
    cout << "单词数：" << wordcount << endl;
    cout << "行数：" << line << endl;
    sort(_words.begin(), _words.end(), sortType);//排序并输出
    for (i = 0; i < _words.size(); ++i)
    {
        cout << _words[i].word << ":" << _words[i].count << endl;
    }
}
void writeFile(const char* filename)
{
    ofstream ofile(filename);
    if (!ofile.good())
    {
        cout << "输出文件打开失败" << endl;
        return;
    }

    vector<Record> _words;
    for (int i = 0; i < duan.size(); ++i) {
        duan[i] = tolower(duan[i]);//转换为小写
    }

    istringstream iss(duan);
    string word;
    int i;
    while (iss >> word)
    {
        for (i = 0; i < _words.size(); ++i)
        {
            if (word == _words[i].word)
            {
                ++_words[i].count;
                break;
            }
        }
        if (i == _words.size())
        {
            Record record;
            record.word = word;
            record.count = 1;
            _words.push_back(record);
        }
    }
    ofile << "字符数：" << character << endl;
    ofile << "单词数：" << wordcount << endl;
    ofile << "行数：" << line << endl;
    sort(_words.begin(), _words.end(), sortType);//排序并输出
    if (_words.size() <= 10) 
    {
        for (int i = 0; i < _words.size(); ++i)
        {
            ofile << _words[i].word << ": " << _words[i].count << endl;
        }
    }
    else
    {
        for (int i = 0; i < 10; ++i)
        {
            ofile << _words[i].word << ": " << _words[i].count << endl;
        }
    }
    ofile.close();
}
int main(int argc, char** argv)
{
    if (argc != 3) {
        cout << "程序出错";
        return 0;
    }
    string in_address1 = argv[1];
    const char* in_address2 = in_address1.data();//将string地址改为char数组
    string out_address1 = argv[2];
    const char* out_address2 = out_address1.data();//将string地址改为char数组
    wordCount(in_address2);//字符统计
    lineCount(in_address2);//行数统计
    characterCount(in_address2);//字符统计
    writeFile(out_address2);//写入文件
    //wordDis();//测试展示
}
