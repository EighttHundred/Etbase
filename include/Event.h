//
// Created by eight on 1/17/20.
//

#ifndef ETBASE_EVENT_H
#define ETBASE_EVENT_H

#include <sys/epoll.h>
#include "Types.h"
#include "Socket.h"

//also involve epoll events
namespace Etbase{
    typedef std::function<void(Socket&)> Handler;
    typedef std::function<void()> Task;

    struct EventConf{
        bool oneshot=false;
        bool et=true;
        bool in=true;
        bool pri=false;
    };

    class Event {
    public:
        int fd=-1;
        Socket sock;
        EventConf conf;
        Priority priority=NORMAL;
    private:
        Task callback;
    public:
        bool operator<(const Event& event)const;
        void setCallback(Task task);
        void doCallback();
    };
    typedef Event* eventPtr;
}



#endif //ETBASE_EVENT_H
