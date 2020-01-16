//
// Created by eight on 1/15/20.
//

#include "Event.h"
#include "Types.h"


Etbase::Event::Event(int fd_):
    fd(fd_),type(IN),priority(NORMAL){
}

Etbase::Event::Event(int fd_, Etbase::Events type_, Etbase::Priority priority_):
    fd(fd_),type(type_),priority(priority_){
}

bool Etbase::Event::operator<(const Etbase::Event &event) const{
    return this->priority<event.priority;
}

