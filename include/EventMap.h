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
        std::map<int,std::shared_ptr<Event>> evmap[2];//0:epollout 1:epollin
        // Mutex mutex;
    public:
        void insert(const Event& event);
        std::shared_ptr<Event> get(int fd,bool in);
    };

    class BufferMap{

    };

    class HandlerMap{

    };

}

#endif //ETBASE_EVENTMAP_H
