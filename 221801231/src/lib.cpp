#include "lib.h"
/*************************************************
 Description:通过对输入的文件流进行逐字符的读取以计算字符数。
 Input: 输入参数分别为fstream类的引用in代表被打开文件的读取流，out代表写入输出文件的输出流.
 Output: 输出值为输出至output文件的字符出现次数// 对输出参数的说明。
 Return:返回字符数量的int值.
 Others:
*************************************************/
int myfile::Countchar(fstream &in, fstream &out)
{

	int totalCount = 0;
	char tempCh;
	in.unsetf(ios_base::skipws);//设置不跳过换行符和空白符
	in >> tempCh;
	while (!in.eof())
	{
		totalCount++;
		in >> tempCh;
	}
	out << "characters: " << totalCount << '\n';
	return totalCount;
}
/*************************************************
 Description:通过对输入的文件流进行逐字符的读取，将读取到的字符拼接为字符串，在遇到分割符后将先前拼接成的字符串进行检查，判断是否为有效的单词，若有效则加入map集合中。无效则跳过。
 Input: 输入参数分别为fstream类的引用in代表被打开文件的读取流，out代表写入输出文件的输出流// 输入参数说明，包括每个参数的作
 // 用、取值说明及参数间关系。
 Output: 输出值为输出至output文件的单词总计出现次数// 对输出参数的说明。
 Return:返回单词数量的int值. // 函数返回值的说明
 Others: // 其它说明
*************************************************/
int myfile::Countword(fstream &in, fstream &out)
{
	bool isWord = true;//判断字符串内容是否符合单词组成
	in.unsetf(ios_base::skipws);//设置不跳过换行符和空白符
	if (!in.is_open())
	{
		cout << "无法打开文件" << endl;
		exit(0);
	}
	int totalCount = 0;
	string wordString = "";
	char temp;
	if (in.eof())
	{
		cout << "文件到达末尾" << endl;
		return -1;
	}
	while (!in.eof())
	{

		in >> temp;
		if (temp <= 'Z'&&temp >= 'A')//如果字符为大写字母将其转换为小写字母
		{
			temp += 32;
		}
		if (!(isalpha(temp)||isdigit(temp)))//判断是否遇到分割符，是则执行以下条件
		{
			if (wordString.length() < 4)//如果单词长度小于4，则直接跳过并清除字符串内容
			{
				wordString = "";
				continue;
			}
			for (int i = 0;i < 4;i++)
			{
				if (!isalpha(wordString[i]))//判断字符串前四位是否为字母，不为字母则直接结束循环
				{
					wordString = "";
					isWord = false;
					break;
				}

			}
			if (!isWord)//如果不为单词则继续执行下一个while循环，不执行以下代码
			{
				isWord = true;
				continue;
			}
			totalCount++;

			//通过find函数判断单词是否在map容器中出现过，若出现过则增加迭代器返回的指针的值既单词次数即可，未出现过则加入新的元素。
			map<string, int>::iterator it = this->wMap.find(wordString);
			if (it != this->wMap.end())
			{
				it->second++;
			}
			else
			{
				this->wMap.insert(pair<string, int>(wordString, 1));
			}
			wordString = "";
		}
		else	wordString = wordString + temp;
	}
	if (!wordString.empty())//当文件读取结束后没有遇到分隔符却字符串中却仍有内容，要进行最后一次检查。
	{
		if (wordString.length() < 4)//如果单词长度小于4，则直接跳过并清除字符串内容
		{
			wordString = "";

		}
		for (int i = 0;i <= 4;i++)
		{
			if (!isalpha(wordString[i]))//判断字符串前四位是否为字母，不为字母则直接结束循环
			{
				wordString = "";
				isWord = false;
				break;
			}

		}
		if (isWord)
		{
			for (int j = 0;j < wordString.length();j++)
			{

				if (wordString[j] <= 'Z'&&wordString[j] >= 'A')
				{
					wordString[j] += 32;
				}
			}
			totalCount++;
			map<string, int>::iterator it = this->wMap.find(wordString);
			if (it != this->wMap.end())
			{
				it->second++;
			}
			else
			{
				this->wMap.insert(pair<string, int>(wordString, 1));
			}
			wordString = "";
		}
		else
		{
			isWord = true;//重置isWord标识符
		}
	}

	out << "words: " << totalCount << endl;//输出单词的数量
	return totalCount;
}
/*************************************************
 Description:通过对输入的文件流进行逐行的读取，统计文件的行数
 Input: 输入参数分别为fstream类的引用in代表被打开文件的读取流，out代表写入输出文件的输出流// 输入参数说明，包括每个参数的作
 // 用、取值说明及参数间关系。
 Output: 输出值为输出至output文件的input文件的总共出现行数// 对输出参数的说明。
 Return:返回行数数量的int值 // 函数返回值的说明
 Others: // 其它说明
*************************************************/
int myfile::Countline(fstream &in, fstream &out)
{
	if (!in.is_open())
	{
		cout << "无法打开文件" << endl;
		exit(0);
	}
	int totalCount = 0;
	string line;
	while (!in.eof())
	{
		getline(in, line);
		for (int i = 0;i < line.length();i++)
		{
			if (!isspace(line[i]))//对文件进行逐行的读取，判断是否存在非空白字符。
			{
				totalCount++;
				break;
			}
		}
	}
	out << "lines: " << totalCount << endl;
	return totalCount;
}
/*************************************************
 Description:作为vector容器中自定义的比较函数比较vector容器中的pair<string,int>元素，首先根据单词出现次数进行比较，若相等map再根据键值字典序排序。
 Input: 输入参数为两个用以比较的pair<string,int>类常量，关系为都为容器中的元素以进行比较。
 Output: 无输出值
 Return:判断两个pair<string,int>类元素之间大小的bool值
 Others: // 其它说明
*************************************************/
bool Sortwordtimes(const pair<string, int> &wordA, const pair<string, int> &wordB)
{
	if (wordA.second == wordB.second)
	{
		return wordA.first < wordB.first;
	}
	return wordA.second > wordB.second;

}
/*************************************************
 Description:将map容器的内容拷贝到vector,在经过线性的vector排序，通过vector容器的迭代器遍历将计算后所得单词出现的次数前十高的单词名与出现次数写入输出文件。
 Input: 输入参数分别为fstream类的引用out代表需要输出文件的流.
 Output: 输出值为输出至output文件的单词名与单词出现次数.
 Return:无return值
 Others:
*************************************************/
void myfile::Sortmap(fstream &out)
{
	vector< pair<string, int> > vec(this->wMap.begin(), this->wMap.end());
	sort(vec.begin(), vec.end(), Sortwordtimes);
	if (vec.size() < 10)
	{
		for (int i = 0;i < vec.size();i++)
		{
			out << vec[i].first << ": " << vec[i].second << endl;
		}
	}
	else
	{
		for (int i = 0;i < 10;i++)
		{
			out << vec[i].first << ": " << vec[i].second << endl;
		}
	}
}
