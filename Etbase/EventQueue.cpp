//
// Created by eight on 1/17/20.
//

#include "../include/EventQueue.h"

size_t Etbase::EventQueue::size() {
    Guard guard(mutex);
    return evqueue.size();
}

void Etbase::EventQueue::push(const Etbase::Event &event) {
    Guard guard(mutex);
    evqueue.push(event);
    if(empty){
        empty=false;
        cond.signal();
    }
}

Etbase::Event Etbase::EventQueue::get() {
    Guard guard(mutex);
    while(empty) cond.wait();
    Event event=evqueue.top();
    evqueue.pop();
    if(evqueue.empty()) empty=true;
    return event;
}