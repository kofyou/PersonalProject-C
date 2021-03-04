#include"Lib.h"


int CountChar(char* filename)
{
	int charcnt = 0;
	char c;
	ifstream f;

	f.open(filename, ios::in);
	ofstream outf("output.txt");

	while (f.get(c))
	{
		charcnt++;
	}
	outf << "characters: " << charcnt << endl;
	f.close();

	return charcnt;
}

int CountWord(char* filename)//统计词数
{
	string s;
	vector<int> ans;//存分隔符位置
	int wordcnt = 0;

	ifstream f;
	f.open(filename, ios::in);
	ofstream outf("output.txt", ios::app);

	while (f >> s) //一次读取一个字符串，读取字符串不包括换行和空格和制表符
	{

		ans.clear();
		int ssize = s.size();
		for (int i = 0; i < ssize; i++)
		{
			if (s[i] >= 'A' && s[i] <= 'Z')//不区分大小写 统一转化为小写
			{
				s[i] += 32;
			}
			if (s[i] < 48 || (s[i] > 57 && s[i] < 65) || (s[i] > 90 && s[i] < 97) || s[i]>122)
			{
				ans.push_back(i);
			}
		}

		if (ans.size() == 0)//如果分割符数目等于0，就是只有一个字符串
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

		for (int i = 0; i < ans.size(); i++)
		{
			//满足分隔符后四个字符是字母
			if ((s[ans[i] + 1] >= 'a' && s[ans[i] + 1] <= 'z') && (s[ans[i] + 2] >= 'a' && s[ans[i] + 2] <= 'z') &&
				(s[ans[i] + 3] >= 'a' && s[ans[i] + 3] <= 'z') && (s[ans[i] + 4] >= 'a' && s[ans[i] + 4] <= 'z'))
			{
				wordcnt++;
			}
		}
	}
	outf << "words: " << wordcnt << endl;
	f.close();

	return wordcnt;

}

int CountLine(char* filename)
{
	ifstream f;
	f.open(filename, ios::in);
	ofstream outf("output.txt", ios::app);

	int linecnt = 0;
	char c;
	int lineflag = 0;


	while (f.get(c))
	{

		if (c != ' ' && c != '\t' && c != '\n')
		{
			lineflag = 1;
		}
		else if (c == '\n' && lineflag == 1) {
			linecnt++;
			lineflag = 0;
		}

	}

	if (lineflag == 1)linecnt++;

	outf << "lines: " << linecnt << endl;

	f.close();

	return linecnt;

}


void CountAndSort(char* filename, vector<pair<string, int>>& x)//统计词数词频
{
	map<string, int> mapp;
	string s;
	vector<int> ans;//存分隔符位置

	ifstream f;
	f.open(filename, ios::in);

	while (f >> s) //一次读取一个字符串，读取字符串不包括换行和空格和制表符
	{

		ans.clear();
		int i;
		int ssize = s.size();
		for (i = 0; i < ssize; i++)
		{
			if (s[i] >= 'A' && s[i] <= 'Z')
			{
				s[i] += 32;
			}
			if (s[i] < 48 || (s[i] > 57 && s[i] < 65) || (s[i] > 90 && s[i] < 97) || s[i]>122)
			{
				ans.push_back(i);
			}
		}
		int sss = ans.size();

		if (sss == 0)//如果分割符数目等于0，就是只有一个字符串
		{
			//如果从该符号起四个字符都是字母
			if ((s[0] >= 97 && s[0] <= 122) && (s[1] >= 97 && s[1] <= 122) && (s[2] >= 97 && s[2] <= 122) && (s[3] >= 97 && s[3] <= 122))
			{
				mapp[s]++;
			}
			continue;
		}

		//否则就有一个以上的分隔符
		//先判断第一个，因为第一个没有分隔符做开头标记
		if ((s[0] >= 97 && s[0] <= 122) && (s[1] >= 97 && s[1] <= 122) && (s[2] >= 97 && s[2] <= 122) && (s[3] >= 97 && s[3] <= 122))
		{
			string temp(s.substr(0, ans[0]));//满足前四个字符是字母，截取
			mapp[temp]++;
		}

		for (i = 0; i < sss; i++)
		{
			//满足分隔符后四个字符是字母
			if ((s[ans[i] + 1] >= 97 && s[ans[i] + 1] <= 122) && (s[ans[i] + 2] >= 97 && s[ans[i] + 2] <= 122) &&
				(s[ans[i] + 3] >= 97 && s[ans[i] + 3] <= 122) && (s[ans[i] + 4] >= 97 && s[ans[i] + 4] <= 122))
			{
				string a;
				if (i == sss - 1)
				{
					string temp(s.substr(ans[i] + 1, s.size() - ans[i] - 1));
					a = temp;
				}
				else
				{
					string temp(s.substr(ans[i] + 1, ans[i + 1] - ans[i] - 1));
					a = temp;
				}
				mapp[a]++;
			}
		}
	}


	f.close();

	/*vector<pair<string, int>> w(mapp.begin(), mapp.end());//词频排序
	x=w;
	sort(x.begin(), x.end(), SortByValue());*/


	vector<pair<string, int>> v(mapp.begin(), mapp.end());//词频排序


	for (int i = 0; i < mapp.size(); i++)
	{
		if (i == 10) break;
		int max = 0;
		string maxword;
		int enflag = 0;
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
				vec->second = -1;
				break;
			}

		}
	}


}


int Display(vector<pair<string, int>>& x)
{
	int vecflag = 0;
	ofstream outf("output.txt", ios::app);

	for (vector<pair<string, int>>::iterator vec = x.begin(); vec != x.end(); vec++)
	{

		cout << vec->first << ":" << vec->second << endl;
		outf << vec->first << ":" << vec->second << endl;
		vecflag++;
		if (vecflag == 10) break;

	}

	return vecflag;
}