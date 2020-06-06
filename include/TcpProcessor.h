#ifndef ETBASE_TCPPROCESSOR_H
#define ETBASE_TCPPROCESSOR_H
#include "EventMap.h"
#include "Epoll.h"
namespace Etbase{
    class TcpProcessor{
        EventMap &eventMap;
        Epoll &acceptor;
        TaskMap &taskMap;
        BufferMap &bufferMap;
        EventConf &readConf;
        EventConf &writeConf;
        EventConf &acceptConf;
    public:
        TcpProcessor(Epoll &acceptor,EventMap &eventMap,BufferMap &bufferMap,
            HandlerMap &taskMap,EventConf &readConf,
            EventConf &writeConf,EventConf &acceptConf);
        void updateEvent(int fd,EventConf conf);
        void addListenEvent(const Socket &socket);
        void addReadEvent(const Socket &socket);
        void addWriteEvent(const Socket &socket);
        void addHandler(int fd,Handler handler);
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