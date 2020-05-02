#ifndef ETBASE_PROCESSOR_H
#define ETBASE_PROCESSOR_H
#include "EventMap.h"
namespace Etbase{
    class Processor{
        HandlerMap *handlerMapPtr;
    public:
        void doRead(const Socket &sock,Buffer &buffer);
        void doRead_Z();
        void doRead_G();
        void doRead_L();
        void doRead_L_EAGAIN();
        void doWrite(const Socket &sock,const Buffer &buffer);
        void doWrite_Z();
        void doWrite_G();
        void doWrite_L_EAGAIN();
    };
}
#endif