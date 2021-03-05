#include "WordCount.h"

int GetCharacters(char *str)
{
	return strlen(str);
}

int GetWords(char* str)
{
	char temp[MAXWORD][MAXWORD];
	int j = 0;
	int num = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] != ' '&&str[i]!='\n')
		{
			temp[num][j] = str[i];
			j++;
		}
		if (j == strlen(str))
		{
			if (j >= 4)
			{
				if ((('a' <= temp[num][0] && temp[num][0] <= 'z') || ('A' <= temp[num][0] && temp[num][0] <= 'Z')) &&
					(('a' <= temp[num][1] && temp[num][1] <= 'z') || ('A' <= temp[num][1] && temp[num][1] <= 'Z')) &&
					(('a' <= temp[num][2] && temp[num][2] <= 'z') || ('A' <= temp[num][2] && temp[num][2] <= 'Z')) &&
					(('a' <= temp[num][3] && temp[num][3] <= 'z') || ('A' <= temp[num][3] && temp[num][3] <= 'Z')))
				{
					return 1;
				}
				
			}
		}
		else if (str[i] == ' '||i == strlen(str)-1||str[i]=='\n')
		{
			if (j >= 4)
			{
				if ((('a' <= temp[num][0] && temp[num][0] <= 'z') || ('A' <= temp[num][0] && temp[num][0] <= 'Z')) &&
					(('a' <= temp[num][1] && temp[num][1] <= 'z') || ('A' <= temp[num][1] && temp[num][1] <= 'Z')) &&
					(('a' <= temp[num][2] && temp[num][2] <= 'z') || ('A' <= temp[num][2] && temp[num][2] <= 'Z')) &&
					(('a' <= temp[num][3] && temp[num][3] <= 'z') || ('A' <= temp[num][3] && temp[num][3] <= 'Z')))
				{
					num++;
				}
			}
			j = 0;
		}
		if (num == 11)
		{
			break;
		}
	}
	return num;
}

int GetLines(char* str)
{
	int n = strlen(str);
	int num = 0;
	if (str[n - 1] == '\n')
	{
		num--;
	}
	for (int i = 0; i < n; i++)
	{
		if (str[i] == '\n')
		{
			if (str[i + 1] != '\n')
			{
				num++;
			}
		}
	}
	return num+1;
}

void Show(string str[], int n,string filename)
{
	ofstream outFile(filename, ios::app);
	int a[MAXWORD] = { 0 };
	for (int i = 0; i < n; i++)
	{
		int k = 1;
		if (str[i] != "0")
		{
			for (int j = i + 1; j < n; j++)
			{
				if (str[i] == str[j] && str[i] != "0")
				{
					k++;
					str[j] = "0";
				}
			}
			a[i] = k;
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i] > a[j])
			{
				swap(a[i], a[j]);
				swap(str[i], str[j]);
			}
		}
	}
	if (n > 10)
	{
		n = 10;
	}
	for (int i = 0; i < n; i++)
	{
		if (a[i] != 0)
		{
			cout << str[i] << ":" << a[i] << endl;
			outFile << str[i] << ":" << a[i] << endl;
		}
	}
	outFile << "------------" << "NEXT"<< "------------" <<endl;
	outFile.close();
}

void GetNumbers(char* str,string filename)
{
	char temp[MAXWORD][MAXWORD] = {0};
	int j = 0;
	int num = 0;
	string strx[MAXWORD] = {};

	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] != ' ' && str[i] != '\n')
		{
			temp[num][j] = str[i];
			j++;
		}
		else if (str[i] == ' ' || i == strlen(str) - 1 || str[i] == '\n')
		{
			if (j >= 4)
			{
				if ((('a' <= temp[num][0] && temp[num][0] <= 'z') || ('A' <= temp[num][0] && temp[num][0] <= 'Z')) &&
					(('a' <= temp[num][1] && temp[num][1] <= 'z') || ('A' <= temp[num][1] && temp[num][1] <= 'Z')) &&
					(('a' <= temp[num][2] && temp[num][2] <= 'z') || ('A' <= temp[num][2] && temp[num][2] <= 'Z')) &&
					(('a' <= temp[num][3] && temp[num][3] <= 'z') || ('A' <= temp[num][3] && temp[num][3] <= 'Z')))
				{
					num++;
				}
			}
			j = 0;
		}
	}
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < MAXWORD; j++)
		{
			if (temp[i][j] != 0)
			{
				strx[i]+=temp[i][j];
			}
		}
	}
	Show(strx, num,filename);
}
