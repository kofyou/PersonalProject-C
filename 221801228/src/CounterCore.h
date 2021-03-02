#pragma once
#ifndef COUNTER_CORE_H_
#define COUNTER_CORE_H_
#include<map>
#include<string>
#include<fstream>
#include<vector>
#include<cctype>

namespace Core
{

class CountResult
{

public:
    int charCount;
    int wordCount;
    int lineCount;
    std::map<std::string, int> wordOccurs;
};


class Counter
{
public:
    static CountResult count(const std::string &file);

    Counter(const std::string &file);

    void setFile(const std::string &file);

    CountResult count();
    CountResult getResult();

private:
    std::string fileName;
    CountResult result;
    bool hasResult;

    inline bool isDivision(char c)
    {
        return !std::isalnum(c);
    }

    std::vector<std::string> splitLines(std::ifstream &is);
    void countWords(std::vector<std::string> &lines);
    void countChars(std::vector<std::string> &lines);
    void countLines(std::vector<std::string> &lines);

    std::vector<std::string> split(const std::string &source);
    std::string toLower(std::string source);
};

}



#endif