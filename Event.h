//
// Created by eight on 1/17/20.
//

#ifndef ETBASE_EVENT_H
#define ETBASE_EVENT_H

#include "Types.h"
#include "Socket.h"

namespace Etbase{
    typedef std::function<void(Socket)> Handler;
    class Event {
    public:
        int fd=-1;
        Socket sock;
        EventType eventType=IN;
        Priority priority=NORMAL;
        Handler handler;
        bool operator<(const Event& event)const;
    };
}



#endif //ETBASE_EVENT_H
