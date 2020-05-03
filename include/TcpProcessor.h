#ifndef ETBASE_TCPPROCESSOR_H
#define ETBASE_TCPPROCESSOR_H
#include "EventMap.h"
#include "Epoll.h"
namespace Etbase{
    class TcpProcessor{
        EventConf readConf;
        EventConf writeConf;
        EventConf acceptConf;
        EventMap &eventMap;
        Epoll &acceptor;
        HandlerMap handlerMap;
        void addHandler(int fd,bool in,Handler handler);
    public:
        void addReadHandler(int fd,Handler handler);
        void addWriteHandler(int fd,Handler handler);
        void setReadConf(const EventConf &conf);
        void setWriteConf(const EventConf &conf);
        void setAcceptConf(const EventConf &conf);
        void doAccept(EventPtr eventPtr);
        void doRead(EventPtr eventPtr);
        void doRead_Z(EventPtr eventPtr);
        void doRead_G(EventPtr eventPtr);
        void doRead_L(EventPtr eventPtr);
        void doRead_L_EAGAIN(EventPtr eventPtr);
        void doWrite(EventPtr eventPtr);
        void doWrite_Z(EventPtr eventPtr);
        void doWrite_G(EventPtr eventPtr);
        void doWrite_L_EAGAIN(EventPtr eventPtr);
        void doWrite_L(EventPtr eventPtr);
    };
}
#endif