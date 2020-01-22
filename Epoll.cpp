//
// Created by eight on 1/15/20.
//
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cassert>
#include "Epoll.h"
#include "Types.h"

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
        Event event=evmap.get(connfd);
        evqueue.push(event);
    }
}

bool Etbase::Epoll::add(const Event& event) {
    epoll_event epollEvent;
    epollEvent.data.fd = event.fd;
    epollEvent.events = EPOLLIN;
    if(et){
        epollEvent.events|=EPOLLET|EPOLLONESHOT;
        assert(setNonBlock(event.fd));
    }
    //is reentrant?
    return epoll_ctl(epfd,EPOLL_CTL_ADD,event.fd,&epollEvent)!=-1;
}

bool Etbase::Epoll::remove(int fd) {
    epoll_event eevent{};
    eevent.data.fd = fd;
    return epoll_ctl(epfd,EPOLL_CTL_DEL,fd,&eevent)!=-1;
}

bool Etbase::Epoll::setNonBlock(int fd) {
    int flags=fcntl(fd,F_GETFL,0);
    if(flags!=-1){
        flags |= O_NONBLOCK;
        if(fcntl(fd,F_SETFL,flags)!=-1) return true;
    }
    return false;
}

bool Etbase::Epoll::resetOneShot(int fd) {
    epoll_event event;
    event.data.fd=fd;
    event.events=EPOLLIN|EPOLLET|EPOLLONESHOT;
    return epoll_ctl(epfd,EPOLL_CTL_MOD,fd,&event)==0;
}


