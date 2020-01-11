#ifndef ETBASE_EPOLLER_H
#define ETBASE_EPOLLER_H

#include "log.h"
#include "types.h"
#include "eventmap.h"
#include <sys/epoll.h>
#include <malloc.h>

#define MAXEVENTS 64

namespace Etbase
{
    class Epoller {
    public:
        Epoller();
        ~Epoller();
        int dispatch(EventMap* emap);
        int addEvent(int fd);
    private:
        int efd;
        epoll_event* events;
    };
}
#endif //ETBASE_EPOLLER_H
