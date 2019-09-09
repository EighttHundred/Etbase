#ifndef ETBASE_EVENT_H
#define ETBASE_EVENT_H

#include "types.h"
namespace Etbase
{
    class Event
    {
    public:
        Event(int fd_,funcp func,void* data);   
        ~Event();
        void setEvent(int fd_,funcp func,void* data);
        void setLevel(int level_);
        int getFd();
        int getLevel();
        evhandler task;
    private:
        int fd;
        int level;
    };
}

#endif // !ETBASE_EVENT_H