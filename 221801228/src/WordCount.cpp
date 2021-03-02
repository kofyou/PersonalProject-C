#include <fstream>
#include <string>
#include <iostream>
#include "CounterCore.h"




int main(int argc, char** argv)
{
    using namespace std;
    if (argc != 3)
    {
        cout << "usage: WordCount <inputfile> <outputfile>\n";
        exit(-1);
    }

    std::string inputFile(argv[1]);
    std::string outputFile(argv[2]);

    auto result = Core::Counter::count(inputFile);
    cout << "characters: " << result.charCount << endl;
    cout << "words: " << result.wordCount << endl;
    cout << "lines: " << result.lineCount << endl;
    return 0;
}