//
// Created by eight on 1/17/20.
//

#ifndef ETBASE_EVENT_H
#define ETBASE_EVENT_H

#include "Types.h"
namespace Etbase{

    class Event {
        typedef std::function<void(int)> Handler;
    public:
        int fd=-1;
        FdType type=CLIENT;
        Priority priority=NORMAL;
        Handler handler;
        bool operator<(const Event& event)const;
    };
}



#endif //ETBASE_EVENT_H
