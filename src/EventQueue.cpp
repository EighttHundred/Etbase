//
// Created by eight on 1/17/20.
//

#include "../include/EventQueue.h"
using namespace Etbase;
size_t EventQueue::size() {
    Guard guard(mutex);
    return evqueue.size();
}

void EventQueue::push(EventPtr eventPtr) {
    Guard guard(mutex);
    evqueue.push(eventPtr);
    if(empty){
        empty=false;
        cond.signal();
    }
}

EventPtr EventQueue::get() {
    Guard guard(mutex);
    cond.wait();
    if(evqueue.empty())
        return nullptr;
    auto eventPtr=evqueue.top();
    evqueue.pop();
    if(evqueue.empty()) empty=true;
    return eventPtr;
}

Etbase::EventQueue::~EventQueue() {
    cond.broadcast();
}
