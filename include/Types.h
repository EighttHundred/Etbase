//
// Created by eight on 1/15/20.
//

#ifndef ETBASE_TYPES_H
#define ETBASE_TYPES_H

#include <functional>


namespace Etbase
{
    enum Priority{
        LOW,NORMAL,HIGH
    };
    enum FdType{
        SERVER,CLIENT
    };
    enum EventType{
        IN,OUT
    };
}

#endif //ETBASE_TYPES_H
