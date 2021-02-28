#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <malloc.h>
using namespace std;

class analysisFlie
{
public:
    analysisFlie countChar(char *, analysisFlie);
    analysisFlie countWord();
    analysisFlie countLine();

private:
    int chars;
    int words;
    int lines;
};

analysisFlie analysisFile::countChar(char *a, analysisFlie b)
{
    int i = 0;
    ifstream file1;
    file1.open(a);
    if (!file1.is_open)
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
    b.characters = i;
    file1.close();
    return b;
}

analysisFlie analysisFlie::countLine()
{
}

analysisFlie analysisFlie::countWord()
{
}

int main(int argc, char *argv[])
{
}