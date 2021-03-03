#include <iostream>
#include <algorithm>
#include "CounterCore.h"

void writeResult(const Core::CountResult& result, const std::string &file)
{
    std::ofstream os(file, std::ios_base::trunc);
    if (!os.is_open())
        throw std::exception(("can not write file " + file + "\n").c_str());
    os << "characters: " << result.charCount << std::endl;
    os << "words: " << result.wordCount << std::endl;
    os << "lines: " << result.lineCount << std::endl;

    using WordPair = std::pair<std::string, int>;
    std::vector<WordPair> words(result.wordOccurs.begin(), result.wordOccurs.end());
    std::stable_sort(words.begin(), words.end(),
        [](const WordPair& a, const WordPair& b)
        {
            return a.second > b.second;
        }
    );

    for (size_t i = 0; i < 10 && i < words.size(); i++)
        os << words[i].first << ": " << words[i].second << std::endl;
    os.close();
}


int main(int argc, char** argv)
{
    using namespace std;
    if (argc != 3)
    {
        cout << "usage: " << argv[0] << " <inputfile> <outputfile>\n";
        exit(EXIT_FAILURE);
    }

    std::string inputFile(argv[1]);
    std::string outputFile(argv[2]);

    try
    {
        auto result = Core::Counter::count(inputFile);
        writeResult(result, outputFile);
    }
    catch (exception e)
    {
        cout << e.what();
        exit(EXIT_FAILURE);
    }

    return 0;
}