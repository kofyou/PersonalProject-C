#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
string duan="";
int wordcount = 0;
int line = 0;
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
void readText(const char* filename) 
{
    ifstream ifile(filename);
    if (!ifile.good())//打开不正常
    {
        cout << "ifstream open file error" << endl;
        return;
    }

    char para[10000];
    int i;
    int j = 0;
    
    while (!ifile.eof()) 
    {
        line++;
        ifile.getline(para, 10000);
        i = 0;
        while (para[i]!='\0') 
        {

            //if (para[i] == ' ') {
              //  character++;
            //}
            
            
            while (wordTest(para[i]))
            {
                character++;
                //duan = duan + para[i];
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

    }
    ifile.close();
    
}
void wordDis()
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

    sort(_words.begin(), _words.end(), sortType);//排序并输出
    for (i = 0; i < _words.size(); ++i) 
    {
        cout << _words[i].word << ":"<<_words[i].count<<endl;
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
    ofile << "行数：" << line - 1 << endl;
    cout << duan << endl;
    sort(_words.begin(), _words.end(), sortType);//排序并输出
    for (int i = 0; i < _words.size(); ++i)
    {
        ofile << _words[i].word << " " << _words[i].count << endl;
    }
    ofile.close();
}
int main(int argc, char** argv)
{
    //string address1 = argv[1];
    //ifstream ifile(address1);
    //string s = "";
    //while (getline(ifile, s)) {
    //    cout << s << endl;
    //}
    //if (argc != 3) {
        //cout << argv[0];
    //}
    
    string in_address1 = argv[1];
    const char* in_address2 = in_address1.data();
    string out_address1 = argv[2];
    const char* out_address2 = out_address1.data();
    readText(in_address2);
    writeFile(out_address2);
    wordDis();
}
