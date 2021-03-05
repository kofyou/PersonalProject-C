#include "cir.h"

bool isAscil(char temp) 
{ 
	if (temp > 122 || temp < 48)
	{
		return true;
	}
	else if (temp < 65 && temp > 57)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool isWhite(char temp) 
{ 
	if (temp == ' ' || temp == '\n'|| temp == '\t')
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool isWord(char temp) 
{ 
	if ((temp >= 'a' && temp <= 'z') || (temp >= 'A' && temp <= 'Z') || (temp >= '0' && temp <= '9'))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isDigit(char temp)
{
	if (temp >= '0' && temp <= '9')
	{
		return true;
	}
	else
	{
		return false;
	}
}

Wordcount::Wordcount()
{
	character = 0;
	word = 0;
	line = 0;
}

Wordcount::Wordcount(string s)
{
	filename = s;
	character = 0;
	word = 0;
	line = 0;
}

void Wordcount::get_all()
{
	get_character();
	get_word();
	get_line();
	result << "characters: " << character << endl;
	result << "words: " << word << endl;
	result << "lines: " << line << endl;
	get_mostword();
}

bool Dic_word(const string& a, const string& b)
{
	if (a < b)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 单词排序 
bool Set_word(const words& a, const words& b)
{
	if (a.num == b.num)
	{
		return a.word < b.word;
	}
	else
	{
		return a.num > b.num;
	}
}

char temp;

void Wordcount::get_character()
{
	ifstream file(filename);
	if (!file)
	{
		cerr << "open error!" << endl;
		exit(1);
	}

	file >> noskipws;// 记录所有字符 
	while (file >> temp)
	{
		character++;
	}
	file.close();

}

void Wordcount::get_line()
{
	ifstream file(filename);
	if (!file)
	{
		cerr << "open error!" << endl;
		exit(1);
	}

	int ef = 0; 
	file >> noskipws;// 记录所有字符 

	while (file >> temp)
	{
		if (!isWhite(temp))
		{
			ef++; // 空白符之间字符数量
		}
		if (temp == '\n' && ef > 0) 
		{ 
			line++; ef = 0; 
		}// 判断是否为有效行
	}
	if (ef > 0) 
	{ 
		line++; 
		ef = 0; 
	}
}

void Wordcount::get_word()
{
	ifstream file(filename);
	if (!file)
	{
		cerr << "open error!" << endl;
		exit(1);
	}
	file >> noskipws;// 记录所有字符 
	vector<string>::iterator fir, las;
	vector<words>::iterator wit;
	vector<string>tempstr; // 单词容器，存文件所有单词
	string _word; 
	words w;
	int flag = 1, wordlen = 0;
	while (file >> temp)
	{
		if (isAscil(temp))// 判断是否是分隔符
		{
			if (flag = 1 && wordlen > 3)
			{
				transform(_word.begin(), _word.end(), _word.begin(), ::tolower);// 转换为小写 
				word++;
				tempstr.push_back(_word);
			}
			wordlen = 0; 
			flag = 1; 
			_word.clear();
		}
		if (isWord(temp)) // 单词 
		{
			wordlen++;
			if (wordlen < 3)
				if (!digit(temp) && flag == 1)
				{
					char s[2] = { temp,0 };
					_word += temp;
				}
				else flag = 0;
			if (wordlen >= 3 && flag == 1) 
			{ 
				char s[2] = { temp,0 }; 
				_word += temp; 
			}
		}
	} 
	if (flag = 1 && wordlen > 3)
	{
		transform(_word.begin(), _word.end(), _word.begin(), ::tolower);// 转换为小写 
		word++; 
		tempstr.push_back(_word);
	}
	sort(tempstr.begin(), tempstr.end(), Dic_word); //将所有单词字典排序，方便后续统计
	for (las = tempstr.begin(), fir = tempstr.begin() + 1; fir != tempstr.end(); fir++)
	{
		if (*fir != *las)
		{
			w.word = *las;
			w.num = fir - las;
			v.push_back(w);
			las = fir;
		}
	}
	w.word = *las;
	w.num = fir - las;
	v.push_back(w);
	file.close();
}

void Wordcount::get_mostword()
{
	sort(v.begin(), v.end(), Set_word);
	if (v.size() <= 10)
	{
		for (int i = 0; i < v.size(); i++)
		{
			result  << v[i].word << ": " << v[i].num << endl;//<<"word frequency: " << (float)v[i].num / word << endl;
		}
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			result  << v[i].word << ": " << v[i].num << endl;//<<"word frequency: " << (float)v[i].num / word << endl;
		}
	}
	result.close();
}