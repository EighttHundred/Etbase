//
// Created by eight on 1/13/20.
//

#ifndef ETBASE_ACCEPTOR_H
#define ETBASE_ACCEPTOR_H

#include <memory>
#include "Types.h"
namespace Etbase{
    class Acceptor{
    public:
        explicit Acceptor(const EventQueue& evqueue_,const PriMap & primap_):
            evqueue(std::make_shared<EventQueue>(evqueue_)),
            primap(std::make_shared<PriMap>(primap_)){}
        virtual void wait(int timeout)=0;
        virtual bool add(const Event& event)=0;
        virtual bool remove(const Event& event)=0;
        virtual bool modify(const Event& event)=0;
    protected:
        std::shared_ptr<EventQueue> evqueue;
        std::shared_ptr<PriMap> primap;
    };
}


#endif //ETBASE_ACCEPTOR_H
