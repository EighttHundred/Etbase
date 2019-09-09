#include "event.h"

Etbase::Event::Event(int fd_,funcp func,void* data)
{
    level=NORMAL;
    setEvent(fd_,func,data);
}

void Etbase::Event::setEvent(int fd_,funcp func,void* data)
{
    fd=fd_;
    task=std::bind(func,data);
}

void Etbase::Event::setLevel(int level_)
{
    level=level_;
}

int Etbase::Event::getFd()
{
    return fd;
}

int Etbase::Event::getLevel()
{
    return level;
}
