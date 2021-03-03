#include"Lib.h"

wordCount::wordCount(string inFileName, string outFileName)
{
	infile.open(inFileName);
	outfile.open(outFileName);
	if (!infile.is_open())
	{
		cout << "文件打开失败" << endl;
	}
	singleWord = "";
	characterCnt = 0;
	wordCnt = 0;
	cnt = 0;
}

wordCount::~wordCount()
{
	infile.close();
	outfile.close();
}

void wordCount::handleInPut() {
	while (infile.get(singleCharacter))
	{
		handleCharacter(singleCharacter);
	}
	wordBreak();
}

void wordCount::outPut()
{
	outfile << "characters: " << cnt << endl;
	outfile << "words：" << wordCnt << endl;
	for (int j = 0; j < wordCnt && j < 10; ++j)
	{
		string key;
		int value = 0;
		map<string, int>::iterator temp;
		for (map<string, int>::iterator i = wordList.begin(); i != wordList.end(); ++i)
		{
			if (i->second > value)
			{
				key = i->first;
				value = i->second;
				temp = i;
			}
		}
		wordList.erase(temp);
		outfile << key << ": " << value << endl;
	}
}

int wordCount::newWord(string key,int value)
{
	wordList.insert(pair<string, int>(key, value));
	wordCnt++;
	return wordCnt;
}

bool wordCount::isRepeatWord()
{
	map<string, int>::iterator iter = wordList.find(singleWord);
	if (iter != wordList.end())
	{
		iter->second ++;
		return true;
	}
	return false;
}

void wordCount::wordBreak()
{
	if (characterCnt >= MIN_WORD_SIZE && !isRepeatWord())
	{
		newWord(singleWord, 1);
	}
	singleWord = "";
	characterCnt = 0;
}

int wordCount::handleCharacter(char c)
{
	if (isalnum(singleCharacter))
	{
		if (isalpha(singleCharacter))
		{
			if (isupper(singleCharacter))
			{
				singleCharacter += 32;//统一转换成小写字母
			}
			characterCnt++;
			singleWord += singleCharacter;
		}
		else
		{
			if (characterCnt >= MIN_WORD_SIZE)
			{
				characterCnt++;
				singleWord += singleCharacter;
			}
		}
	}
	else
	{
		wordBreak();
	}
	cnt++;
	return cnt;
}
