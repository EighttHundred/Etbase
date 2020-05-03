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
        bool empty=true;
        std::priority_queue<EventPtr> evqueue;
        Mutex mutex;
        Condition cond=Condition(mutex);
    public:
        ~EventQueue();
        void push(EventPtr eventPtr);
        EventPtr get();
        size_t size();
    };
}



#endif //ETBASE_EVENTQUEUE_H
