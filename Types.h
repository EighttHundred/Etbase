//
// Created by eight on 1/15/20.
//

#ifndef ETBASE_TYPES_H
#define ETBASE_TYPES_H

#include <functional>
#include <queue>
#include <map>

namespace Etbase
{
    enum Events{
        IN,OUT,ERR
    };
    enum Priority{
        LOW,NORMAL,HIGH
    };

    class Event {
    public:
        int fd;
        Events type;
        Priority priority;
    public:
        explicit Event(int fd_);
        Event(int fd_,Events type_,Priority priority_);
        bool operator<(const Event& event)const;
    };

    typedef std::map<int,Priority> PriMap;
    typedef std::function<void()> Handler;
    typedef std::map<Event,Handler> HandlerMap;
    typedef std::priority_queue<Event> EventQueue;

}

#endif //ETBASE_TYPES_H
