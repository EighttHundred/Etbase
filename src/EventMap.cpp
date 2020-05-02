//
// Created by eight on 1/17/20.
//

#include "../include/EventMap.h"
using namespace Etbase;

void EventMap::insert(const Event &event) {
    //lock whole map
    // Guard guard(mutex);
    evmap[event.conf.in][event.fd]=std::make_shared<Event>(event);
}

std::shared_ptr<Event> EventMap::get(int fd, bool flag) {
    // Guard guard(mutex);
    auto iter=evmap[flag].find(fd);
    if(iter!=evmap[flag].end()) return iter->second;
    else return nullptr;
}


