//
// Created by eight on 1/17/20.
//

#include "../include/Event.h"

#include <utility>

bool Etbase::Event::operator<(const Etbase::Event &event) const {
    return this->priority<event.priority;
}

void Etbase::Event::setCallback(Etbase::Task task) {
    callback=std::move(task);
}

void Etbase::Event::doCallback() {
    callback();
}
