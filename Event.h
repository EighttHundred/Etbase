//
// Created by eight on 1/17/20.
//

#ifndef ETBASE_EVENT_H
#define ETBASE_EVENT_H

#include "Types.h"
#include "Socket.h"

namespace Etbase{

    class Event {
        typedef std::function<void(Socket)> Handler;
    public:
        int fd=-1;
        Socket sock;
        FdType type=CLIENT;
        Priority priority=NORMAL;
        Handler handler;
        bool operator<(const Event& event)const;
    };
}



#endif //ETBASE_EVENT_H
