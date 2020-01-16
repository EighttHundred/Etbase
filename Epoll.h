//
// Created by eight on 1/16/20.
//

#ifndef ETBASE_EPOLL_H
#define ETBASE_EPOLL_H

#include <sys/epoll.h>
#include "Acceptor.h"

namespace Etbase{
    class Epoll:Acceptor{
        int fd;
        bool et=false;
        const static int MAXEVENT=64;
        epoll_event events[MAXEVENT]{};
    public:
        Epoll(const EventQueue& evqueue_,const PriMap& primap_);
        ~Epoll();
        void wait(int timeout) override;
        bool add(const Event& event) override;
        bool remove(const Event& event) override;
        bool modify(const Event& event) override;
    };
}
#endif //ETBASE_EPOLL_H
