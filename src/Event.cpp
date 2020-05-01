//
// Created by eight on 1/17/20.
//

#include "../include/Event.h"

#include <utility>

using namespace Etbase;
bool Event::operator<(const Event &event) const {
    return this->priority<event.priority;
}

void Event::setCallback(Task task) {
    callback=std::move(task);
}

void Event::doCallback() {
    callback();
}
Event& Event::operator=(const Event& event){
    this->fd=event.fd;
    this->conf=event.conf;
    this->sock=event.sock;
    this->callback=event.callback;
}

Event::Event(){
    fd=-1;
}

Event::Event(Socket sock_,EventConf conf_,Task callback_){
    fd=sock_.getFd();
    sock=sock_;
    conf=conf_;
    callback=callback_;
}

EventConf getConfigedConf(bool oneshot,bool et,bool in,bool pri){
    EventConf conf;
    conf.oneshot=oneshot;
    conf.et=et;
    conf.in=in;
    conf.pri=pri;
    return conf;
}