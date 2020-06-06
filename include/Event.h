//
// Created by eight on 1/17/20.
//

#ifndef ETBASE_EVENT_H
#define ETBASE_EVENT_H

#include <sys/epoll.h>
#include <map>
#include "Types.h"
#include "Socket.h"
#include "Buffer.h"
#include "Mutex.h"
//also involve epoll events
namespace Etbase{
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
        // Task callback=nullptr;
        // Buffer buffer;
        Mutex mutex;
    public:
        Event(Socket sock_,EventConf conf_);
        Event& operator=(const Event& event);
        bool operator<(const Event& event)const;
        // void setTask(Task task);
        // void setBuffer(const Buffer &buffer);
        Socket& getSocket();
        // Buffer& getBuffer();
        // void runTask();
    };
    typedef std::shared_ptr<Event> EventPtr;
    typedef std::function<void(EventPtr,BufferPtr)> Handler;
    typedef std::map<int,EventPtr> EventMap;
    typedef std::map<int,Handler> HandlerMap;
    typedef std::map<int,Task> TaskMap;
}



#endif //ETBASE_EVENT_H
