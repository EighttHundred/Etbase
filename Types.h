//
// Created by eight on 1/15/20.
//

#ifndef ETBASE_TYPES_H
#define ETBASE_TYPES_H

#include <functional>


namespace Etbase
{
    typedef std::function<void()> Handler;

    enum Events{
        IN,OUT,ERR
    };
    enum Priority{
        LOW,NORMAL,HIGH
    };
}

#endif //ETBASE_TYPES_H
