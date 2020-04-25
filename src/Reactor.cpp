//
// Created by eight on 1/15/20.
//

#include "../include/Reactor.h"
using namespace Etbase;

Reactor::Reactor():
    pool(evqueue),acceptor(evqueue,evmap) {
}

void Reactor::run() {
    acceptor.run();
}

Reactor::~Reactor() {
    stop=true;
}

void Reactor::loop() {
    while(!stop){
        std::vector<std::vector<Timer>::iterator> removeList;
        for(auto timer=timerList.begin();timer!=timerList.end();++timer){
            if(timer->check()){
                timer->runTask();
            }else if(!timer->checkAlive()){
                removeList.push_back(timer);
            }
        }
        for(auto ip=removeList.end();removeList.end()!=removeList.begin()&&(ip--)!=removeList.begin();){
            timerList.erase(*ip);
        }
        run();
        if(!checkActive()){
            stop=true;
        }
    }
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


void Reactor::start() {
    stop=false;
    for(auto timer:timerList){
        timer.begin();
    }
    pool.start();
    loop();
}

void Reactor::addMap(const Event &event) {
    evmap.insert(event);

}

bool Reactor::addAcceptor(const Event &event) {
    return acceptor.add(event);
}

void Reactor::addTimer(const Timer &timer) {
    timerList.push_back(timer);
}

bool Reactor::checkActive() {
    return !(timerList.empty() && reactorConf.canStop);
}

bool Reactor::addEvent(const Event &event) {
    addMap(event);
    return addAcceptor(event);
}

ReactorConf Reactor::getConf() {
    return reactorConf;
}

void Reactor::setConf(const ReactorConf &conf) {
    reactorConf=conf;
}
