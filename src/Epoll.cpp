//
// Created by eight on 1/15/20.
//
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cassert>
#include "../include/Epoll.h"
#include "../include/Types.h"
using namespace Etbase;

Epoll::Epoll( EventQueue &evqueue_, EventMap& evmap_) :
    Acceptor(evqueue_,evmap_),epfd(epoll_create1(0)) {
}

Epoll::~Epoll() {
    close(epfd);
}

void Epoll::run() {
    int n = ::epoll_wait(epfd, events, MAXEVENT, timeout);
    if(n==-1){
        std::cout<<"epoll wait error "<<errno<<std::endl;
        return;
    }
    for (int i = 0; i < n; ++i){
        int connfd = events[i].data.fd;
        evqueue.push(evmap[connfd]);
    }
}

bool Epoll::add(EventPtr eventPtr) {
    epoll_event epollEvent=eventParser(eventPtr->fd,eventPtr->conf);
    return epoll_ctl(epfd,EPOLL_CTL_ADD,eventPtr->fd,&epollEvent)!=-1;    //is reentrant?
}

bool Epoll::remove(int fd) {
    epoll_event eevent{};
    eevent.data.fd = fd;
    return epoll_ctl(epfd,EPOLL_CTL_DEL,fd,&eevent)!=-1;
}

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
