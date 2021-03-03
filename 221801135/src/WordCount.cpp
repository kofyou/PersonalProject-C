#include"Lib.h"
int main(int argc, char* argv[])
{
	ifstream infile(argv[1]);
	ofstream outfile(argv[2]);
	char singleCharacter;
	string singleWord="";
	map<string, int> wordList;
	int characterCnt = 0;
	int wordCnt = 0;
	int cnt = 0;
	map<string, int>::iterator iter;
	if (!infile.is_open()) 
	{
		cout << "文件打开失败" << endl;
	}
	while (infile.get(singleCharacter))
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
			if (characterCnt >= MIN_WORD_SIZE)
			{
				iter = wordList.find(singleWord);
				if (iter != wordList.end())
				{
					int value;
					string key;
					value = iter->second+1;
					key = iter->first;
					wordList.erase(iter);
					wordList.insert(pair<string, int>(key, value));
				}
				else 
				{
					wordList.insert(pair<string, int>(singleWord, 1));
					singleWord = "";
					characterCnt = 0;
					wordCnt++;
				}
			}
			else
			{
				singleWord = "";
				characterCnt = 0;
			}
		}
		cnt++;
	}
	if (characterCnt >= MIN_WORD_SIZE)
	{
		iter = wordList.find(singleWord);
		if (iter != wordList.end())
		{
			int value;
			string key;
			value = iter->second + 1;
			key = iter->first;
			wordList.erase(iter);
			wordList.insert(pair<string, int>(key, value));
		}
		else
		{
			wordList.insert(pair<string, int>(singleWord, 1));
			singleWord = "";
			characterCnt = 0;
			wordCnt++;
		}
	}
	if (infile.is_open())
	{
		infile.close();
	}

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
	return 0;
}
