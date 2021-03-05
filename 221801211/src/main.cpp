#include "WordCount.h"

int main(int argc, char** argv)
{
	ifstream inFile;
	inFile.open(argv[1]);
	ofstream outFile(argv[2],ios::app);
	string filename = argv[2];
	char buffer[MAXWORDS] = {};
	long i = 0;
	char x;
	while ((x=inFile.get())!=EOF)
	{
		if (x <= 'z' && x >= 'a')
		{
			x = x - 32;
		}
		buffer[i] = x;
		i++;
	}
	cout << "characters:" << GetCharacters(buffer) << endl;
	cout << "words:" << GetWords(buffer) << endl;
	cout << "lines:" << GetLines(buffer) << endl;
	outFile << "characters:" << GetCharacters(buffer) << endl;
	outFile << "words:" << GetWords(buffer) << endl;
	outFile << "lines:" << GetLines(buffer) << endl;
	outFile.close();
	GetNumbers(buffer, filename);
}