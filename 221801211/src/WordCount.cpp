#include "БъЭЗ.h"

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
		if (str[i] != ' ')
		{
			temp[num][j] = str[i];
			j++;

		}
		if (j == strlen(str))
		{
			if (j >= 4)
			{
				return 1;
			}
		}
		else if (str[i] == ' '||i == strlen(str)-1)
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
	return num;
}

