#pragma once
#ifndef COUNTER_CORE_H_
#define COUNTER_CORE_H_
#include<map>
#include<string>
#include<fstream>
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

    Counter(std::ifstream & is);
    Counter(const std::string &file);

    void setFile(std::ifstream & is);
    void setFile(const std::string &file);

    CountResult count();
    CountResult getResult() const;

    ~Counter();

private:
    std::ifstream *istream;
    bool isMeOpen; //标志文件是否由Counter打开
};

}



#endif