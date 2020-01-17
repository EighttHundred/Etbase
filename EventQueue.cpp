//
// Created by eight on 1/17/20.
//

#include "EventQueue.h"

bool Etbase::EventQueue::pop() {
    Guard guard(mutex);
    if(!evqueue.empty()){
        evqueue.pop();
        return true;
    }else return false;
}

Etbase::Event Etbase::EventQueue::top() {
    Guard guard(mutex);
    if(!evqueue.empty()) return evqueue.top();
    else return Event();
}

size_t Etbase::EventQueue::size() {
    Guard guard(mutex);
    return evqueue.size();
}

void Etbase::EventQueue::push(const Etbase::Event &event) {
    Guard guard(mutex);
    evqueue.push(event);
}
