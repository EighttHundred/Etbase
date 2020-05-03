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
    struct ReactorConf{
        bool canStop=true;

    };
    class Reactor {
        EventMap evmap;
        EventQueue evqueue;
        Epoll acceptor;
        ThreadPool pool;
        ReactorConf reactorConf;
        bool stop= true;
        std::vector<Timer> timerList;
    public:
        Reactor();
        ~Reactor();
        void start();
        void run();
        void loop(); //-1:loop forever
        bool checkActive();
        // bool updateEvent(int fd,const EventConf &conf);
        // bool addEvent(const Event& event);
        void addTimer(const Timer& timer);
        EventPtr getEvent(int fd,bool in);
        ReactorConf getConf();
        void setConf(const ReactorConf& conf);
    };

}



#endif //ETBASE_REACTOR_H
