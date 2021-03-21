#include"Lib.h"


int CountChar(char* filein, char* fileout)
{
	int charcnt = 0;
	char c;

	ifstream f(filein, ios::in);
	ofstream outf(fileout);

	while (f.get(c))
	{
		charcnt++;
	}
	outf << "characters: " << charcnt << endl;
	f.close();

	return charcnt;
}

int CountWord(char* filein, char* fileout)//统计词数
{
	string s;
	vector<int> separators;//存分隔符位置
	int wordcnt = 0;

	ifstream f(filein, ios::in);
	ofstream outf(fileout, ios::app);

	while (f >> s) //一次读取一个字符串，读取字符串不包括换行、空格和制表符
	{

		separators.clear();
		int s_size = s.size();
		for (int i = 0; i < s_size; i++)
		{
			if (s[i] >= 'A' && s[i] <= 'Z')//不区分大小写 统一转化为小写
			{
				s[i] += 32;
			}
			if (s[i] < 48 || (s[i] > 57 && s[i] < 65) || (s[i] > 90 && s[i] < 97) || s[i]>122)
			{
				separators.push_back(i);
			}
		}

		if (separators.size() == 0)//如果没有分隔符，就是只有一个字符串
		{
			//如果从该符号起四个字符都是字母
			if ((s[0] >= 'a' && s[0] <= 'z') && (s[1] >= 'a' && s[1] <= 'z') && (s[2] >= 'a' && s[2] <= 'z') && (s[3] >= 'a' && s[3] <= 'z'))
			{
				wordcnt++;
			}
			continue;
		}

		//否则就有一个以上的分隔符
		//先判断第一个，因为第一个没有分隔符做开头标记
		else if ((s[0] >= 'a' && s[0] <= 'z') && (s[1] >= 'a' && s[1] <= 'z') && (s[2] >= 'a' && s[2] <= 'z') && (s[3] >= 'a' && s[3] <= 'z'))
		{
			wordcnt++;
		}

		for (int i = 0; i < separators.size(); i++)
		{
			//满足分隔符后四个字符是字母
			if ((s[separators[i] + 1] >= 'a' && s[separators[i] + 1] <= 'z') && (s[separators[i] + 2] >= 'a' && s[separators[i] + 2] <= 'z') &&
				(s[separators[i] + 3] >= 'a' && s[separators[i] + 3] <= 'z') && (s[separators[i] + 4] >= 'a' && s[separators[i] + 4] <= 'z'))
			{
				wordcnt++;
			}
		}
		Sleep(1);
	}
	outf << "words: " << wordcnt << endl;
	f.close();

	return wordcnt;

}

int CountLine(char* filein, char* fileout)
{
	int linecnt = 0;
	char c;
	int lineflag = 0;

	ifstream f(filein, ios::in);
	ofstream outf(fileout, ios::app);


	while (f.get(c))
	{

		if (c != ' ' && c != '\t' && c != '\n')
		{
			lineflag = 1;
		}
		else if (c == '\n' && lineflag == 1)
		{
			linecnt++;
			lineflag = 0;
		}
		
	}

	if (lineflag == 1)linecnt++;

	outf << "lines: " << linecnt << endl;

	f.close();

	return linecnt;

}


void CountMaxWord(char* filein, vector<pair<string, int>>& x)//统计词数词频
{
	map<string, int> time;//存单词名和次数
	string s;
	vector<int> separators;//存分隔符位置

	ifstream f(filein, ios::in);

	while (f >> s) //一次读取一个字符串，读取字符串不包括换行和空格和制表符
	{

		separators.clear();
		int i;
		int s_size = s.size();
		for (i = 0; i < s_size; i++)
		{
			if (s[i] >= 'A' && s[i] <= 'Z')
			{
				s[i] += 32;
			}
			if (s[i] < 48 || (s[i] > 57 && s[i] < 65) || (s[i] > 90 && s[i] < 97) || s[i]>122)
			{
				separators.push_back(i);
			}
		}
		int separators_size = separators.size();

		if (separators_size == 0)//如果分割符数目等于0，就是只有一个字符串
		{
			//如果从该符号起四个字符都是字母
			if ((s[0] >= 97 && s[0] <= 122) && (s[1] >= 97 && s[1] <= 122) && (s[2] >= 97 && s[2] <= 122) && (s[3] >= 97 && s[3] <= 122))
			{
				time[s]++;
			}
			continue;
		}
		
		//否则就有一个以上的分隔符
		//先判断第一个，因为第一个没有分隔符做开头标记
		else if ((s[0] >= 97 && s[0] <= 122) && (s[1] >= 97 && s[1] <= 122) && (s[2] >= 97 && s[2] <= 122) && (s[3] >= 97 && s[3] <= 122))
		{
			string temp(s.substr(0, separators[0]));//满足前四个字符是字母，截取
			time[temp]++;
		}

		for (i = 0; i < separators_size; i++)
		{
			//满足分隔符后四个字符是字母
			if ((s[separators[i] + 1] >= 97 && s[separators[i] + 1] <= 122) && (s[separators[i] + 2] >= 97 && s[separators[i] + 2] <= 122) &&
				(s[separators[i] + 3] >= 97 && s[separators[i] + 3] <= 122) && (s[separators[i] + 4] >= 97 && s[separators[i] + 4] <= 122))
			{
				string a;
				if (i == separators_size - 1)
				{
					string temp(s.substr(separators[i] + 1, s.size() - separators[i] - 1));
					a = temp;
				}
				else
				{
					string temp(s.substr(separators[i] + 1, separators[i + 1] - separators[i] - 1));
					a = temp;
				}
				time[a]++;
			}
		}
		
	}

	vector<pair<string, int>> v(time.begin(), time.end());//词频排序

	for (int i = 0; i < time.size(); i++)
	{
		if (i == 10) break;//最多取10个
		int max = 0;//最大出现次数
		string maxword;//对应单词名
		for (vector<pair<string, int>>::iterator vec = v.begin(); vec != v.end(); vec++)
		{
			if (vec->second > max)
			{
				max = vec->second;//存下当前最大数单词
				maxword = vec->first;
			}
			else if (vec->second == max)//字典序
			{
				if (vec->first < maxword)
				{
					max = vec->second;//存下当前最大数单词
					maxword = vec->first;
				}
			}
		}

		if (max) x.push_back(make_pair(maxword, max));

		for (vector<pair<string, int>>::iterator vec = v.begin(); vec != v.end(); vec++)
		{
			if (vec->first == maxword)
			{
				vec->second = -1;//出现次数置-1
				break;
			}

		}

	}
	f.close();
}

int WriteToFile(char* fileout, vector<pair<string, int>>& x)
{
	int veccnt = 0;
	for (vector<pair<string, int>>::iterator vec = x.begin(); vec != x.end(); vec++)
	{

		ofstream outf(fileout, ios::app);

		cout << vec->first << ": " << vec->second << endl;
		outf << vec->first << ": " << vec->second << endl;

		veccnt++;
		if (veccnt == 10) break;

	}
	return veccnt;
}

//void test(char* fileout)
//{
//	ofstream outf(fileout);
//	for (int i = 0; i < 30000; i++) {
//		outf << "apple123 " << endl;
//	}
//}