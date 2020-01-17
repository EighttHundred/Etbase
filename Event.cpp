//
// Created by eight on 1/17/20.
//

#include "Event.h"

bool Etbase::Event::operator<(const Etbase::Event &event) const {
    return this->priority<event.priority;
}
