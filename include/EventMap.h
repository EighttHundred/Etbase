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
        std::map<int,Event> evmap[2];
        Mutex mutex;
    public:
        void insert(const Event& event);
        void modify(const Event& event);
        bool remove(int fd,bool flag);
        Event get(int fd,bool flag);
    };

}

#endif //ETBASE_EVENTMAP_H
