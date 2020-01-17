//
// Created by eight on 1/17/20.
//

#include "EventMap.h"

void Etbase::EventMap::insert(int fd, const Etbase::Event &event) {
    //lock whole map
    Guard guard(mutex);
    evmap[fd]=event;
}

void Etbase::EventMap::modify(int fd, const Etbase::Event &event) {
    Guard guard(mutex);
    evmap[fd]=event;
}

bool Etbase::EventMap::remove(int fd) {
    Guard guard(mutex);
    auto iter=evmap.find(fd);
    if(iter!=evmap.end()){
        evmap.erase(iter);
        return true;
    }else return false;
}
