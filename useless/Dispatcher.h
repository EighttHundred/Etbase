//
// Created by eight on 1/16/20.
//

#ifndef ETBASE_DISPATCHER_H
#define ETBASE_DISPATCHER_H

#include <memory>
#include "../EventMap.h"
#include "../EventQueue.h"
namespace Etbase{

    class Dispatcher {
    public:
        Dispatcher(const EventQueue& evqueue_,const EventMap & evmap_):
            evqueue(std::make_shared<EventQueue>(evqueue_)),
            evmap(std::make_shared<EventMap>(evmap_)){
        }
        virtual int dispatch()=0;
    protected:
        std::shared_ptr<EventQueue> evqueue;
        std::shared_ptr<EventMap> evmap;
    };

}



#endif //ETBASE_DISPATCHER_H
