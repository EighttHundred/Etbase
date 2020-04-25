//
// Created by eight on 1/17/20.
//

#include "../include/EventMap.h"
using namespace Etbase;

void Etbase::EventMap::insert(const Etbase::Event &event) {
    //lock whole map
    Guard guard(mutex);
    evmap[event.conf.in][event.fd]=event;
}

void Etbase::EventMap::modify(const Etbase::Event &event) {
    Guard guard(mutex);
    evmap[event.conf.in][event.fd]=event;
}

Event EventMap::get(int fd, bool flag) {
    Guard guard(mutex);
    auto iter=evmap[flag].find(fd);
    if(iter!=evmap[flag].end()) return iter->second;
    else return Event();
}

bool EventMap::remove(int fd, bool flag) {
    Guard guard(mutex);
    auto iter=evmap[flag].find(fd);
    if(iter!=evmap[flag].end()){
        evmap[flag].erase(iter);
        return true;
    }else return false;
}
