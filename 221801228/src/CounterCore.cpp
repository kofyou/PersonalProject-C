#define  _CRT_SECURE_NO_WARNINGS
#include"CounterCore.h"
#include<stdexcept>
#include<iostream>
#include<stdio.h>


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
    FileType encoding = checkFileType(fileName);
    if (encoding != FileType::UTF8 && encoding != FileType::UTF8BOM)
        throw std::invalid_argument(
            ("file " + fileName + " is not an UTF-8 encoding file\n").c_str());

    FILE* file = fopen(fileName.c_str(), "rb");

    std::string word;
    char c = '\0';
    bool readingWord = false;
    bool ignore = false;
    bool isLine = false;

    if (encoding == FileType::UTF8BOM)
        fseek(file, 3, SEEK_SET);

    while (fread(&c, sizeof(c), 1, file) != 0)
    {
        if (isascii(c))
            result.charCount++;

        if (!isascii(c) || !isspace(c))
            isLine = true;

        if (c == '\n')
        {
            if (isLine)
                result.lineCount++;

            isLine = false;
        }
        bool isDvsn = isDivision(c);
        if (!isDvsn && !ignore)
        {
            if (!readingWord && !isalpha(c))
                ignore = true;
            else
            {
                readingWord = true;
                word.push_back(toLower(c));
            }
        }

        if (isDvsn)
            ignore = false;
        if (isDvsn && readingWord)
        {
            readingWord = false;
            if (isWord(word))
            {
                result.wordOccurs[word] += 1;
                result.wordCount++;
            }
            word.clear();
        }
    }
    if (isLine)
        result.lineCount++;
    if (readingWord && isWord(word))
    {
        result.wordCount++;
        result.wordOccurs[word] += 1;
    }
<<<<<<< HEAD
    
=======

>>>>>>> 6128fba61d9aa03280f56cc309f8ec95eed53bbc
    fclose(file);

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
        throw std::ios::failure(("open " + fileName + " failed\n").c_str());

    unsigned char c;
    fin.read((char*)&c, sizeof(c));
    if (c <= 127)
    {
        fin.close();
        return FileType::UTF8;
    }
    int flag = c << 8;
    fin.read((char*)&c, sizeof(c));
    flag |= c;

    fin.close();

    if (flag == 0xefbb)
        return FileType::UTF8BOM;
    return FileType::OTHER;
}

Core::CountResult Core::Counter::count(const std::string &file)
{
    return Core::Counter(file).count();
}