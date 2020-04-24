//
// Created by eight on 1/15/20.
//

#include "../include/Reactor.h"
using namespace Etbase;

Reactor::Reactor():
    pool(8,evqueue),acceptor(evqueue,evmap) {
}

bool Reactor::regist(const Event &event) {
    evmap.insert(event);
    return acceptor.add(event);
}

void Reactor::run() {
    acceptor.run();
}

Reactor::~Reactor() {
    stop=true;
}

void Reactor::loop(int times) {
    if(times==-1)
        while(!stop) run();
    else
        while(times--) run();
}

Epoll *Reactor::getPoller() {
    return &acceptor;
}

bool Reactor::remove(int fd) {
    return acceptor.remove(fd);
}


