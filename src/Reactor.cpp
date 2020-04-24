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

void Reactor::loop() {
    if(timer){
        if(timer->check()){
            timer->runTask();
        }else if(timer->getTimes()==0&&(userType&2)==0){
            stop=true;
        }
    }
    while(!stop) run();
}

Epoll *Reactor::getPoller() {
    return &acceptor;
}

bool Reactor::remove(int fd) {
    return acceptor.remove(fd);
}

void Reactor::setTimeout(int timeout) {
    acceptor.setTimeout(timeout);
}

void Reactor::initTimer(Timer *timer_) {
    timer=timer_;
}

void Reactor::init(int timeout) {
    setTimeout(timeout);
}

void Reactor::setUserType(int type) {
    userType=type;
}

void Reactor::start() {
    stop=false;
    if(timer) timer->begin();
    loop();
}

