#include"CounterCore.h"
#include<exception>
#include<iostream>

Core::Counter::Counter(const std::string &file)
{
    setFile(file);
}

void Core::Counter::setFile(const std::string &file)
{
    fileName = file;
}

Core::CountResult Core::Counter::count()
{
    if (checkFileType(fileName) != FileType::UTF8)
        throw std::exception(("file " + fileName + " is not an UTF-8 encoding file\n").c_str());

    std::ifstream is(fileName, std::ios::basic_ios::binary);
    result = CountResult();

    std::string word;
    char pre = '\0';
    char c;
    bool readingWord = false;
    bool ignore = false;
    bool isLine = false;

    //跳过UTF-8文件前三个字符EF BB BF
    is.read(&c, sizeof(c));
    is.read(&c, sizeof(c));
    is.read(&c, sizeof(c));

    while (is.read(&c, sizeof(c)))
    {
        if (c >= -1 && c <= 255 && isascii(c))
            result.charCount++;

        if (!isascii(c) || !isspace(c))
            isLine = true;

        if (c == '\n')
        {
            if (isLine)
                result.lineCount++;

            if (readingWord)
            {
                readingWord = false;
                result.wordOccurs[word] += 1;
                word.clear();
            }
            isLine = false;
        }

        if (!isDivision(c) && !ignore)
        {
            if (!readingWord && !(isascii(c) && isalpha(c)))
                ignore = true;
            else
            {
                readingWord = true;
                word.push_back(c);
            }
        }
        if (isDivision(c) && readingWord)
        {
            readingWord = false;
            result.wordOccurs[word] += 1;
            word.clear();
        }
    }
    if (isLine)
        result.lineCount++;

    is.close();
    result.wordCount = result.wordOccurs.size();

    return result;
}

char Core::Counter::toLower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    else
        return c;
}

Core::FileType Core::Counter::checkFileType(const std::string &file)
{
    std::ifstream fin(file, std::ios_base::binary);
    if (!fin.is_open())
        throw std::exception(("open " + fileName + " failed\n").c_str());

    unsigned char c;
    fin.read((char*)&c, sizeof(c));
    int flag = c << 8;
    fin.read((char*)&c, sizeof(c));
    flag |= c;

    fin.close();

    if (flag == 0xefbb)
        return FileType::UTF8;
    return FileType::OTHER;
}

Core::CountResult Core::Counter::count(const std::string &file)
{
    return Core::Counter(file).count();
}