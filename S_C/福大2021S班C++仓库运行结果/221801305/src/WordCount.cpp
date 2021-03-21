#include "WordCount.h"

int main(int argc, char* argv[])
{
    char* inFile = argv[1];
    char* outFile = argv[2];
    int chNumber = 0;
    int wordNumber = 0;
    int lineNumber = 0;

    chNumber = countCharacter(inFile);
    wordNumber = countWord(inFile);
    lineNumber = countLine(inFile);
    sortWord();
    printResult(outFile, chNumber, lineNumber, wordNumber);

    return 0;
}
