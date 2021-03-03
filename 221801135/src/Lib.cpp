#include"Lib.h"
void inPut(string fileName) {
	infile.open(fileName);
	if (!infile.is_open())
	{
		cout << "文件打开失败" << endl;
	}
	while (infile.get(singleCharacter))
	{
		handleCharacter(singleCharacter);
	}
	wordBreak();
	if (infile.is_open())
	{
		infile.close();
	}
}

void outPut(string fileName)
{
	outfile.open(fileName);
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

	outfile.close();
}

bool newWord(string key,int value)
{
	wordList.insert(pair<string, int>(key, value));
	wordCnt++;
	return true;
}

bool isRepeatWord()
{
	map<string, int>::iterator iter = wordList.find(singleWord);
	if (iter != wordList.end())
	{
		iter->second ++;
		return true;
	}
	return false;
}

void wordBreak()
{
	if (characterCnt >= MIN_WORD_SIZE && !isRepeatWord())
	{
		newWord(singleWord, 1);
	}
	singleWord = "";
	characterCnt = 0;
}

void handleCharacter(char c) 
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
}
