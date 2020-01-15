//
// Created by eight on 1/15/20.
//

#ifndef ETBASE_EPOLL_H
#define ETBASE_EPOLL_H

#include <sys/epoll.h>
#include "Acceptor.h"

namespace Etbase{
    class Epoll:Acceptor {
        const int fd;
        epoll_event events{};
    public:
        Epoll();
        ~Epoll();
        void accpet();
    private:

    public:
        int wait(EventMap* emap);
        int add(int fd);
    };
}



#endif //ETBASE_EPOLL_H
