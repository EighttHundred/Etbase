//
// Created by eight on 1/15/20.
//

#ifndef ETBASE_REACTOR_H
#define ETBASE_REACTOR_H

#include <memory>
#include "Acceptor.h"
#include "Types.h"
#include "Epoll.h"

namespace Etbase{

    class Reactor {
        PriMap priMap;
        EventQueue evQueue;
        HandlerMap handlerMap;
        std::shared_ptr<Epoll> acceptor;
    public:
        Reactor();
        void loopOnce();
        void loop();
        bool add(const Event& event,const Handler& handler);
    };

}



#endif //ETBASE_REACTOR_H
