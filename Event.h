//
// Created by eight on 1/17/20.
//

#ifndef ETBASE_EVENT_H
#define ETBASE_EVENT_H

#include "Types.h"
namespace Etbase{
    class Event {
    public:
        int fd=-1;
        // now useless
        Events type;
        Priority priority;
        Handler handler;
        bool operator<(const Event& event)const;
    };
}



#endif //ETBASE_EVENT_H
