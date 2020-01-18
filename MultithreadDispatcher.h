//
// Created by eight on 1/18/20.
//

#ifndef ETBASE_MULTITHREADDISPATCHER_H
#define ETBASE_MULTITHREADDISPATCHER_H

#include "Dispatcher.h"
namespace Etbase{

    class MultithreadDispatcher:Dispatcher {

    public:
        MultithreadDispatcher(const EventQueue& evqueue_,const EventMap& evmap_);
        int dispatch() override ;
    };
}



#endif //ETBASE_MULTITHREADDISPATCHER_H
