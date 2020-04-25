//
// Created by eight on 1/17/20.
//

#ifndef ETBASE_EVENTMAP_H
#define ETBASE_EVENTMAP_H

#include <map>
#include <memory>
#include "Mutex.h"
#include "Event.h"
namespace Etbase{

    class EventMap {
        std::map<int,Event> evmap[2];//0:epollout 1:epollin
        Mutex mutex;
    public:
        void insert(const Event& event);
        void modify(const Event& event);
        bool remove(int fd,bool flag);
        Event get(int fd,bool flag);
    };

    class BufferMap{
        std::map<int,String> buffMap;
        Mutex mutex;
    public:
        void insert(int fd,const String& buffer);
        String getBuffer(int fd);
        bool removeBuffer(int fd);
    };

}

#endif //ETBASE_EVENTMAP_H
