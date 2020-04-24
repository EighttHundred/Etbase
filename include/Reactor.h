//
// Created by eight on 1/15/20.
//

#ifndef ETBASE_REACTOR_H
#define ETBASE_REACTOR_H

#include <memory>
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
        Timer* timer= nullptr;
        int userType; //0:none 1:sender 2:server 3:both
    public:
        Reactor();
        ~Reactor();
        void start();
        void run();
        void loop(); //-1:loop forever
        bool regist(const Event& event);
        bool remove(int fd);
        void setTimeout(int timeout);
        void init(int timeout);
        void initTimer(Timer* timer_);
        void setUserType(int type);
        Epoll* getPoller();
    };

}



#endif //ETBASE_REACTOR_H
