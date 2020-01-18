//
// Created by eight on 1/15/20.
//

#ifndef ETBASE_REACTOR_H
#define ETBASE_REACTOR_H

#include <memory>
#include "Acceptor.h"
#include "Types.h"
#include "Epoll.h"

namespace Etbase{

    class Reactor {
        EventMap evmap;
        EventQueue evqueue;
        std::shared_ptr<Epoll> acceptor;
    public:
        Reactor();
        void run();
        //loop forever
        void loop(int times=-1);
        bool regist(const Event& event);
        bool remove(int fd);
        bool modify(const Event& event);
        bool active(int fd);
    };

}



#endif //ETBASE_REACTOR_H
