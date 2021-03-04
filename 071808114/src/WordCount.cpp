#include "Lib.h"

using namespace std;

extern int characters;
extern int lines;
extern int words;

int main(int argc, char* argv[])
{
	//异常处理
	if (argv[1] == NULL)
	{
		printf("请输入文件路径\n");
		return -1;
	}
	/*if (argc > 3)
	{
		printf("输入文件过多\n");
		return -1;
	}*/
	int len = strlen(argv[1]);
	if (!(*(argv[1] + len - 1) == 't' &&
		*(argv[1] + len - 2) == 'x' &&
		*(argv[1] + len - 3) == 't'))
	{
		printf("输入文件不是txt形式\n");
		return -1;
	}

	ifstream f;
	f.open(argv[1], ios::in);
	if (!f)
	{
		printf("无法打开文件\n");
		return -1;
	}
	f.close();

	int charsss = CountChar(argv[1]);
	int linesss = CountLine(argv[1]);
	int wordsss = CountWord(argv[1]);

	printf("characters: %d\n", charsss);
	printf("words: %d\n", wordsss);
	printf("lines: %d\n", linesss);

	vector<pair<string, int>> v;
	CountAndSort(argv[1], v);
	int num = Display(v);
	v.clear();


	return 0;
}