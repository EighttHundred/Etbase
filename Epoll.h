//
// Created by eight on 1/16/20.
//

#ifndef ETBASE_EPOLL_H
#define ETBASE_EPOLL_H

#include <sys/epoll.h>
#include "Acceptor.h"

namespace Etbase{
    class Epoll:public Acceptor{
        int epfd;
        bool et=true;
        //infinite wait time
        int timeout=-1;
        const static int MAXEVENT=64;
        epoll_event events[MAXEVENT]{};
    public:
        Epoll( EventQueue& evqueue_, EventMap& evmap_);
        ~Epoll();
        void run() override;
        bool add(const Event& event) override;
        bool remove(int fd_) override;
        bool resetOneShot(int fd);
        bool setNonBlock(int fd);

    };
}
#endif //ETBASE_EPOLL_H
