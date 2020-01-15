#include "eventmap.h"

int Etbase::EventMap::countEvent()
{
    LockGuard lockGuard(mutex);
    return evmap.size();
}

int Etbase::EventMap::countActive()
{
    LockGuard lockGuard(mutex);
    return evqueue.size();
}

int Etbase::EventMap::addMap(Event&& event)
{
    LockGuard lockGuard(mutex);
    int fd=event.getFd();
    if(evmap.find(fd)!=evmap.end()){
        return -1;
    }
    evmap[fd]=event;
    return 1;
}

int Etbase::EventMap::addQueue(int fd)
{
    LockGuard lockGuard(mutex);
    if(evmap.find(fd)==evmap.end()){
        return -1;
    }
    evqueue.push(pair(evmap[fd].getLevel(),fd));
    return 1;
}