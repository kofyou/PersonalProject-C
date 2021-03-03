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
    enum FileType { UTF8, OTHER };

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
        static CountResult count(const std::string& file);

        Counter(const std::string& file);

        void setFile(const std::string& file);

        CountResult count();

    private:
        std::string fileName;
        CountResult result;

        inline bool isDivision(char c)
        {
            return !isascii(c) || !std::isalnum(c);
        }

        char toLower(char c);
        FileType checkFileType(const std::string& file);
    };

}



#endif