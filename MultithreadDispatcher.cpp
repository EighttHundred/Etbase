//
// Created by eight on 1/18/20.
//

#include "MultithreadDispatcher.h"

Etbase::MultithreadDispatcher::MultithreadDispatcher(const Etbase::EventQueue &evqueue_, const Etbase::EventMap &evmap_)
        : Dispatcher(evqueue_, evmap_) {
}

int Etbase::MultithreadDispatcher::dispatch() {
    return 0;
}
