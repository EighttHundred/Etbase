//
// Created by eight on 1/15/20.
//

#include "Reactor.h"

Etbase::Reactor::Reactor() {
    acceptor=std::make_shared<Epoll>(evQueue,priMap);
}

bool Etbase::Reactor::add(const Etbase::Event &event, const Etbase::Handler &handler) {
    return false;
}
