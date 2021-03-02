#include"CounterCore.h"
#include<exception>

Core::Counter::Counter(const std::string &file)
{
    setFile(file);
}

void Core::Counter::setFile(const std::string &file)
{
    fileName = file;
    hasResult = false;
}

Core::CountResult Core::Counter::count()
{
    std::ifstream is(fileName);
    if (!is.is_open())
        throw std::exception(("open " + fileName + " failed\n").c_str());

    result = CountResult();
    std::vector<std::string> lines = splitLines(is);
    is.close();
    countWords(lines);
    countChars(lines);
    return result;
}

Core::CountResult Core::Counter::getResult()
{
    if (hasResult)
        return result;
    else
        return count();
}

std::vector<std::string> Core::Counter::splitLines(std::ifstream &is)
{
    std::vector<std::string> lines;
    std::string line;
    while(std::getline(is, line))
        lines.push_back(line);
    return lines;
}

void Core::Counter::countWords(std::vector<std::string> &lines)
{
    for (auto it = lines.begin(); it != lines.end(); ++it)
    {
        auto words = split(*it);
        result.wordCount += words.size();
        for (int i = 0; i < words.size(); i++)
            result.wordOccurs[words[i]] += 1;
    }
}

void Core::Counter::countChars(std::vector<std::string> &lines)
{
    
}

std::vector<std::string> Core::Counter::split(const std::string &source)
{
    std::vector<std::string> result;
    for (int i = 0; i < source.size(); i++)
    {
        while (i < source.size() && isDivision(source[i]))
            ++i;
        if (i == source.size())
            break;

        int start = i;
        while (i < source.size() && !isDivision(source[i]))
        {
            ++i;
        }

        if (i - start > 3 && std::isalpha(source[start]))
            result.push_back(toLower(source.substr(start, i - start)));
    }

    return result;
}

std::string Core::Counter::toLower(std::string source)
{
    for (int i = 0; i < source.size(); i++)
        if (source[i] >= 'A' && source[i] <= 'Z')
            source[i] += 'a' - 'A';
    return source;
}