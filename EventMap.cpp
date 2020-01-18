//
// Created by eight on 1/17/20.
//

#include "EventMap.h"

void Etbase::EventMap::insert(const Etbase::Event &event) {
    //lock whole map
    Guard guard(mutex);
    evmap[event.fd]=event;
}

void Etbase::EventMap::modify(const Etbase::Event &event) {
    Guard guard(mutex);
    evmap[event.fd]=event;
}

bool Etbase::EventMap::remove(int fd) {
    Guard guard(mutex);
    auto iter=evmap.find(fd);
    if(iter!=evmap.end()){
        evmap.erase(iter);
        return true;
    }else return false;
}

Etbase::Event Etbase::EventMap::get(int fd) {
    Guard guard(mutex);
    auto iter=evmap.find(fd);
    if(iter!=evmap.end()) return iter->second;
    else return Event();
}
