//
// Created by eight on 1/15/20.
//
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cassert>
#include "../include/Epoll.h"
#include "../include/Types.h"

Etbase::Epoll::Epoll( Etbase::EventQueue &evqueue_, Etbase::EventMap& evmap_) :
    Acceptor(evqueue_,evmap_),epfd(epoll_create1(0)) {
}

Etbase::Epoll::~Epoll() {
    close(epfd);
}

void Etbase::Epoll::run() {
    int n = ::epoll_wait(epfd, events, MAXEVENT, timeout);
    if(n==-1){
        std::cout<<"epoll wait error "<<errno<<std::endl;
        return;
    }
    for (int i = 0; i < n; ++i){
        int connfd = events[i].data.fd;
        Event event=evmap.get(connfd,(events[i].events&EPOLLIN)==EPOLLIN);
        evqueue.push(event);
    }
}

bool Etbase::Epoll::add(const Event& event) {
    epoll_event epollEvent=eventParser(event.fd,event.conf);
    return epoll_ctl(epfd,EPOLL_CTL_ADD,event.fd,&epollEvent)!=-1;    //is reentrant?
}

bool Etbase::Epoll::remove(int fd) {
    epoll_event eevent{};
    eevent.data.fd = fd;
    return epoll_ctl(epfd,EPOLL_CTL_DEL,fd,&eevent)!=-1;
}

namespace Etbase{

    bool Epoll::update(int fd, const EventConf &conf) {
        auto epollEvent=eventParser(fd,conf);
        return epoll_ctl(epfd,EPOLL_CTL_MOD,fd,&epollEvent)!=-1;
    }

    epoll_event Epoll::eventParser(int fd, const EventConf &conf) {
        epoll_event res{};
        res.data.fd=fd;
        if(conf.in) res.events|=EPOLLIN;
        else res.events|=EPOLLOUT;
        if(conf.et) res.events|=EPOLLET;
        if(conf.oneshot) res.events|=EPOLLONESHOT;
        if(conf.pri) res.events|=EPOLLPRI;
        return res;
    }

    void Epoll::setTimeout(int timeout_) {
        timeout=timeout_;
    }
}
