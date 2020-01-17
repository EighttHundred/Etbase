//
// Created by eight on 1/15/20.
//

#include <unistd.h>
#include "Epoll.h"
#include "Types.h"

Etbase::Epoll::Epoll(const Etbase::EventQueue &evqueue_,const Etbase::EventMap& evmap_) :
    Acceptor(evqueue_,evmap_),fd(epoll_create(0)) {
}

Etbase::Epoll::~Epoll() {
    close(fd);
}

void Etbase::Epoll::wait(int timeout) {
    int n = ::epoll_wait(fd, events, MAXEVENT, timeout);
    for (int i = 0; i < n; ++i){
        int rcvfd = events[i].data.fd;
        Event event(rcvfd);
        Priority fd_pri=rcvfd==fd?HIGH:LOW;
        auto ptr=primap->find(rcvfd);
        if(ptr!=primap->end()) {
            auto pri=ptr->second;
            if(pri<fd_pri){
                (*primap)[rcvfd]=fd_pri;
                event.priority=fd_pri;
            }else event.priority=pri;
        }else{
            (*primap)[rcvfd]=fd_pri;
            event.priority=fd_pri;
        }
        if(events[i].events&EPOLLERR) event.type=ERR;
        else if(events[i].events&EPOLLIN) event.type=IN;
        else if(events[i].events&EPOLLOUT) event.type=OUT;
        evqueue->push(event);
    }
}

bool Etbase::Epoll::add(const Etbase::Event &event) {
    epoll_event eevent{};
    eevent.data.fd = fd;
    if(event.type==IN) eevent.events = EPOLLIN;
    else if(event.type==OUT) eevent.events=EPOLLOUT;
    if(et) eevent.events|=EPOLLET;
    return epoll_ctl(fd,EPOLL_CTL_ADD,event.fd,&eevent)!=-1;
}

bool Etbase::Epoll::remove(const Etbase::Event &event) {
    epoll_event eevent{};
    eevent.data.fd = fd;
    return epoll_ctl(fd,EPOLL_CTL_DEL,event.fd,&eevent)!=-1;
}

bool Etbase::Epoll::modify(const Etbase::Event &event) {
    epoll_event eevent{};
    eevent.data.fd = fd;
    if(event.type==IN) eevent.events = EPOLLIN;
    else if(event.type==OUT) eevent.events=EPOLLOUT;
    if(et) eevent.events|=EPOLLET;
    return epoll_ctl(fd,EPOLL_CTL_ADD,event.fd,&eevent)!=-1;
}


