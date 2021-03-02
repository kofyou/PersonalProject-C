#include "Lib.h"
int main(int argc, char *argv[])
{
    int i = 0;
    int j = 0;
    int num = 0;
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
    Words *wword1 = new Words[file1.getWords()];
    Words *temp = new Words[file1.getWords()];
    map<string, int>::iterator it;
    it = mapword1.begin();
    for (it; it != mapword1.end(); it++)
    {
        wword1[num].word = it->first;
        wword1[num].count = it->second;
        num++;
    }
    sort(wword1, temp, 0, num - 1);

    Words *p = file1.getsW();
    for (int i = 0; i < file1.getSums(); i++)
    {
        if (i == 10)
            break;
        else
        {
            file2 << wword1[i].word << ": " << wword1[i].count << endl;
        }
    }
}
