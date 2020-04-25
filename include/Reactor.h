//
// Created by eight on 1/15/20.
//

#ifndef ETBASE_REACTOR_H
#define ETBASE_REACTOR_H

#include <memory>
#include <vector>
#include "Acceptor.h"
#include "Types.h"
#include "Epoll.h"
#include "ThreadPool.h"
namespace Etbase{

    class Reactor {
        EventMap evmap;
        EventQueue evqueue;
        Epoll acceptor;
        ThreadPool pool;
        bool stop= true;
        std::vector<Timer> timerList;
        int userType; //0:none 1:sender 2:server 3:both
        void addMap(const Event& event);
        bool addAcceptor(const Event& event);
    public:
        Reactor();
        ~Reactor();
        void start();
        void run();
        void loop(); //-1:loop forever
        bool checkActive();
        bool addEvent(const Event& event);
        bool remove(int fd);
        void setTimeout(int timeout);
        void init(int timeout);
        void addTimer(const Timer& timer);
        void setUserType(int type);
        Epoll* getPoller();
    };

}



#endif //ETBASE_REACTOR_H
