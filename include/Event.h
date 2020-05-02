//
// Created by eight on 1/17/20.
//

#ifndef ETBASE_EVENT_H
#define ETBASE_EVENT_H

#include <sys/epoll.h>
#include "Types.h"
#include "Socket.h"
#include "Buffer.h"
#include "Mutex.h"
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
    EventConf getConfigedConf(bool oneshot,bool et,bool in,bool pri);
    class Event {
    public:
        int fd=-1;
        Socket sock;
        EventConf conf;
        Priority priority=NORMAL;
    private:
        Task callback;
        Buffer buffer;
        Mutex mutex;
    public:
        Event();
        Event(Socket sock_,EventConf conf_,Task callback_);
        Event& operator=(const Event& event);
        bool operator<(const Event& event)const;
        void setTask(Task task);
        void setBuffer(const Buffer &buffer);
        Buffer& getBuffer();
        void runTask();
    };
    typedef Event* eventPtr;
}



#endif //ETBASE_EVENT_H
