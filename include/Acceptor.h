//
// Created by eight on 1/13/20.
//

#ifndef ETBASE_ACCEPTOR_H
#define ETBASE_ACCEPTOR_H

#include "EventMap.h"
#include "EventQueue.h"
namespace Etbase{
    class Acceptor{
    public:
        Acceptor(EventQueue& evqueue_,EventMap & evmap_):
            evqueue(evqueue_),
            evmap(evmap_){
        }
        virtual void run()=0;
        virtual bool add(EventPtr eventPtr)=0;
        virtual bool remove(int fd_)=0;

    public:
        EventQueue& evqueue;
        EventMap& evmap;
    };
}


#endif //ETBASE_ACCEPTOR_H
