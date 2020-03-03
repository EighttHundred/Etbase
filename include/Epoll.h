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
        //infinite wait time
        int timeout=-1;
        const static int MAXEVENT=64;
        epoll_event events[MAXEVENT]{};
        epoll_event eventParser(int fd,const EventConf& conf);
    public:
        Epoll( EventQueue& evqueue_, EventMap& evmap_);
        ~Epoll();
        void run() override;
        bool add(const Event& event) override;
        bool update(int fd,const EventConf& conf);
        bool remove(int fd) override ;
    };
}
#endif //ETBASE_EPOLL_H
