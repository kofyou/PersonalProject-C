#include"CounterCore.h"

Core::Counter::Counter(const std::string &file)
{

}

Core::Counter::Counter(std::ifstream & is)
{

}

void Core::Counter::setFile(const std::string &file)
{

}

void Core::Counter::setFile(std::ifstream & is)
{

}

Core::CountResult Core::Counter::count()
{
    return Core::CountResult();
}

Core::CountResult Core::Counter::getResult() const
{
    return Core::CountResult();
}

Core::Counter::~Counter()
{
    if (istream && isMeOpen && istream->is_open())
        istream->close();
}