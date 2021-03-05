#include "Lib.h"

using namespace std;


int main(int argc, char* argv[])
{
	freopen("unusual.txt","w",stdout);
	//异常处理
	if (argv[1] == NULL || argv[2]==NULL)
	{
		cout << "请输入文件路径" << endl;
		return -1;
	}
	
	if (argc > 3)
	{
		cout << "输入文件过多" << endl;
		return -1;
	}
	
	/*test(argv[1]);*/
	ifstream f;
	f.open(argv[1], ios::in);
	if (!f)
	{
		cout << "无法打开文件" << endl;
		return -1;
	}
	f.close();

	int charcount = CountChar(argv[1],argv[2]);
	int linecount = CountLine(argv[1], argv[2]);
	int wordcount = CountWord(argv[1], argv[2]);

	cout << "characters: " << charcount << endl;
	cout << "words: " << wordcount << endl;
	cout << "lines: " << linecount << endl;


	vector<pair<string, int>> v;
	CountMaxWord(argv[1], v);
	int num = WriteToFile(argv[2], v);
	v.clear();


	return 0;
}