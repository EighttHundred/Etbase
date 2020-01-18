//
// Created by eight on 1/13/20.
//

#ifndef ETBASE_ACCEPTOR_H
#define ETBASE_ACCEPTOR_H

#include <memory>
#include "EventMap.h"
#include "EventQueue.h"
namespace Etbase{
    class Acceptor{
    public:
        Acceptor(const EventQueue& evqueue_,const EventMap & evmap_):
            evqueue(std::make_shared<EventQueue>(evqueue_)),
            evmap(std::make_shared<EventMap>(evmap_)){
        }
        virtual void run()=0;
        virtual bool add(const Event& event)=0;
        virtual bool remove(int fd_)=0;
        virtual bool modify(const Event& event)=0;
    protected:
        std::shared_ptr<EventQueue> evqueue;
        std::shared_ptr<EventMap> evmap;
    };
}


#endif //ETBASE_ACCEPTOR_H
