//
// Created by eight on 1/16/20.
//

#ifndef ETBASE_EPOLL_H
#define ETBASE_EPOLL_H

#include <sys/epoll.h>
#include "Acceptor.h"
#include "Timer.h"
namespace Etbase{
    class Epoll:public Acceptor{
        int epfd;
        //-1:infinite wait time
        int timeout=100;
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
        void setTimeout(int timeout_);
    };
}
#endif //ETBASE_EPOLL_H
