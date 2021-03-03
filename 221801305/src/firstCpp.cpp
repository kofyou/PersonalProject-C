// firstCpp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

void countCharacter(char *inFile,char *outFile)
{
    fstream fin(inFile, ios::in);
    if (!fin.is_open())
    {
        cout << "以读方式打开测试文件失败!" << endl;
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
        cout << "以写方式打开输出文件失败!" << endl;
        exit(0);
    }
    //cout << chNumber << endl;
    fout << "characters: " << chNumber-1 << '\n';//chNumber的结果要去掉BOM的影响
    fout.close();
}

void countLine(char *inFile,char *outFile)
{
    fstream fin(inFile, ios::in);
    if (!fin.is_open())
    {
        cout << "以读方式打开测试文件失败!" << endl;
        exit(0);
    }
    char ch;
    int judge = 0;//用于判断一行中是否存在非空白符的变量
    int lineNumber = 0;
    while (fin.get(ch))
    {
        if (ch == 10)
        {
            if(judge)
                lineNumber++;
            judge = 0;
        }
        if (ch >= 33 && ch <= 126) judge = 1;
    }
    fin.close();

    fstream fout(outFile, ios::app);
    if (!fout.is_open())
    {
        cout << "以写方式打开输出文件失败!" << endl;
        exit(0);
    }
    cout << fout.tellg()<<endl;
    fout << "lines: " << lineNumber << '\n';
    fout.close();
}

int main(int argc,char *argv[])
{
    char *inFile = argv[1];
    char *outFile = argv[2];
    
    countCharacter(inFile,outFile);
    countLine(inFile,outFile);
    //int num_i = atoi(argv[i]);   字符串转换成整数
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
