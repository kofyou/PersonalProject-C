#include "WordCount.h"

int main(int argc, char** argv)
{
	ifstream inFile;
	inFile.open(argv[1]);
	char buffer[MAXWORDS] = {};
	int i = 0;
	char x;
	while ((x=inFile.get())!=EOF)
	{
		buffer[i] = x;
		i++;
	}
	cout << "characters:" << GetCharacters(buffer) << endl;
	cout << "words:" << GetLines(buffer) << endl;
	cout << "lines:" << GetWords(buffer) << endl;
	GetNumbers(buffer);
}