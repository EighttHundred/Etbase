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
        bool stop= false;
    public:
        Reactor();
        ~Reactor();
        void run();
        void loop(int times=-1); //-1:loop forever
        bool regist(const Event& event);
        bool remove(int fd);
        Epoll* getPoller();
    };

}



#endif //ETBASE_REACTOR_H
