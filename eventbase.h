#ifndef ETBASE_EVENTBASE_H
#define ETBASE_EVENTBASE_H

#include "threadpool.h"
#include "epoller.h"
#include "eventmap.h"
#include "event.h"

namespace Etbase
{
    class EventBase
    {
    public:
        EventBase();
        ~EventBase();
        int addEvent(Event&& event);
        int removeEvent(int fd);
        
        void beginLoop();
    private:
        Epoller epoller;
        ThreadPool pool;
        EventMap evmap;
    };
}

#endif // !ETBASE_EVENTBASE_H