#ifndef ETBASE_EVENTMAP_H
#define ETBASE_EVENTMAP_H

#include "event.h"
#include "types.h"
#include "mutex.h"
#include <map>
namespace Etbase
{
    class EventMap
    {
    public:
        int countEvent();
        int countActive();
        int addMap(Event&& event);
        int addQueue(int fd);
        Event* getEvent(int fd);
        Event* getFront();
        int removeEvent(int fd);
        int removeFront();
    private:
        Mutex mutex;
        std::map<int,Event> evmap;
        pri_queue evqueue;
    };
}

#endif // !ETBASE_EVENTMAP_H