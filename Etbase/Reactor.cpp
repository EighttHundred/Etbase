//
// Created by eight on 1/15/20.
//

#include "../include/Reactor.h"

Etbase::Reactor::Reactor():
    pool(8,evqueue),acceptor(evqueue,evmap) {
}

bool Etbase::Reactor::regist(const Etbase::Event &event) {
    evmap.insert(event);
    return acceptor.add(event);
}

void Etbase::Reactor::modify(const Etbase::Event &event) {
    evmap.modify(event);
}

bool Etbase::Reactor::remove(int fd) {
    evmap.remove(fd);
    return acceptor.remove(fd);
}

void Etbase::Reactor::run() {
    acceptor.run();
}

Etbase::Reactor::~Reactor() {
    stop=true;
}

void Etbase::Reactor::active(int fd) {
    evqueue.push(evmap.get(fd));
}

void Etbase::Reactor::loop(int times) {
    if(times==-1)
        while(!stop) run();
    else
        while(times--) run();
}

Etbase::Epoll *Etbase::Reactor::getPoller() {
    return &acceptor;
}


