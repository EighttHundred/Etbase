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

    // class EventMap {
    //     std::map<int,EventPtr> evmap[2];//0:epollout 1:epollin
    //     // Mutex mutex;
    // public:
    //     void insert(EventPtr eventPtr);
    //     EventPtr get(int fd,bool in);
    // };


    // class HandlerMap{
    //     //not complete
    //     std::map<int,Handler> handlerMap[2];
    // public:
    //     void insert(int fd,bool in,Handler handler);
    //     Handler get(int fd,bool in);
    // };

    // class BufferMap{
    //     std::map<int,Buffer> bufferMap[2];
    // public:
    //     void insert(int fd,Buffer);
    // };
}

#endif //ETBASE_EVENTMAP_H
