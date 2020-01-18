//
// Created by eight on 1/15/20.
//

#include "Reactor.h"

Etbase::Reactor::Reactor() {
    acceptor=std::make_shared<Epoll>(evqueue,evmap);
}

bool Etbase::Reactor::regist(const Etbase::Event &event) {
    evmap.insert(event);
    return acceptor->add(event);
}

bool Etbase::Reactor::modify(const Etbase::Event &event) {
    evmap.modify(event);
    return acceptor->modify(event);
}

bool Etbase::Reactor::remove(int fd) {
    evmap.remove(fd);
    return acceptor->remove(fd);
}

void Etbase::Reactor::run() {
    acceptor->run();

}

//bool Etbase::Reactor::active(int fd) {
//    return false;
//}

