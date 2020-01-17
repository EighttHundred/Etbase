//
// Created by eight on 1/17/20.
//

#ifndef ETBASE_EVENTQUEUE_H
#define ETBASE_EVENTQUEUE_H

#include <queue>
#include "Event.h"
#include "Mutex.h"
namespace Etbase{
    class EventQueue {
        std::priority_queue<Event> evqueue;
        Mutex mutex;
        void push(const Event& event);
        Event top();
        bool pop();
        size_t size();
    };
}



#endif //ETBASE_EVENTQUEUE_H
