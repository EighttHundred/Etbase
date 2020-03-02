//
// Created by eight on 1/17/20.
//

#ifndef ETBASE_EVENT_H
#define ETBASE_EVENT_H

#include "Types.h"
#include "Socket.h"

namespace Etbase{
    typedef std::function<void(Socket&)> Handler;
    typedef std::function<void()> Task;
    class Event {
    public:
        int fd=-1;
        Socket sock;
        EventType eventType=IN;
        Priority priority=NORMAL;
    private:
        Task callback;
    public:
        bool operator<(const Event& event)const;
        void setCallback(Task task);
        void doCallback();
    };
}



#endif //ETBASE_EVENT_H
