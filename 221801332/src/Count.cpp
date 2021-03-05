#include "Count.h"

//计算字符数
int Count::CountCharNum(string& charBuf)
{
	return int(charBuf.size());
}

//计算行数
int Count::CountLineNum(vector<string>& linesBuf)
{
	int lineCount = 0;
	for (int i = 0; i < linesBuf.size(); i++)
	{
		for (string::iterator it = linesBuf[i].begin(); it != linesBuf[i].end(); it++)
		{
			if (*it >= 32&& *it <= 126)  //可打印字符（32~126）
			{
				lineCount++;
				break;
			}
		}
	}
	return lineCount;
}

//计算单词数
int Count::CountWordNum(vector<string>& linesBuf)
{
	int wordCount = 0;
	int linesBufSize = int(linesBuf.size());
	string wordBuf;
	for (int i = 0; i < linesBufSize; i++)
	{
		int len = int(linesBuf[i].length());
		for (int j = 0; j < len; j++)
		{
			if (isLetter(linesBuf[i][j]) || isDigit(linesBuf[i][j]))
			{
				wordBuf += linesBuf[i][j];
			}
			else {
				if (wordBuf.length() >= 4 && isLetter(wordBuf[0]) && isLetter(wordBuf[1]) 
					&& isLetter(wordBuf[2]) && isLetter(wordBuf[3]))
				{
					WordMap[wordBuf]++;
					wordCount++;
				}
				wordBuf = "";
			}
		}
	}
	return wordCount;
}

//统计出现频率最高的10个单词
vector<map<string, int>::iterator>& Count::CountTop10Word()
{
	int WordMapSize = int(WordMap.size());
	for (int i = 0; i < WordMapSize && i < 10; i++)
	{
		auto maxFreWord = WordMap.begin();
		for (map<string, int>::iterator it = WordMap.begin(); it != WordMap.end(); it++)
		{
			if (it->second > maxFreWord->second)
			{
				maxFreWord = it;
			}
		}
		Top10Word.push_back(maxFreWord);
		maxFreWord->second = -maxFreWord->second;
	}
	return Top10Word;
}

//字符串分割函数
vector<string> split(string str, string pattern)
{
	string::size_type pos;
	vector<string> result;
	str += pattern;  //扩展字符串以方便操作
	int size = str.size();
	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

//判断是否为字母
inline bool Count::isLetter(string::iterator it) {
	return (*it >= 97 && *it <= 122);
}

//判断是否为字母(重载)
inline bool Count::isLetter(const char& ch) {
	return (ch >= 97 && ch <= 122);
}

//判断是否为数字
inline bool Count::isDigit(string::iterator it) {
	return *it >= '0' && *it <= '9';
}

//判断是否为数字(重载)
inline bool Count::isDigit(const char& ch) {
	return ch >= '0' && ch <= '9';
}
