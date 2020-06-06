//
// Created by eighthundred on 2020/4/24.
//

#ifndef ETBASE_TCPCONNECTOR_H
#define ETBASE_TCPCONNECTOR_H
#include <memory>
#include <map>
#include "Socket.h"
#include "Reactor.h"
#include "Timer.h"
#include "TcpProcessor.h"
namespace Etbase{
    class TcpConnector {
    private:
        Socket listenSock;
        Socket sendSock;
        EventConf readConf;
        EventConf writeConf;
        EventConf acceptConf;
        Reactor &reactor;
        BufferMap &bufferMap;
        TcpProcessor processor;
        void handleTimer(Timer& timer_);
    public:
        ~TcpConnector();
        void setReadConf(const EventConf &conf);
        void setWriteConf(const EventConf &conf);
        void setAcceptConf(const EventConf &conf);
        void setConnHandler(Handler handler);
        void setSenderHandler(Handler handler);
        void start();
        void initServer(const char* port);
        void initSender(const char* ip,const char* port,int times=1,int timeout=100,int delay=0);
        void setSendData(const Buffer& data);
        TcpConnector(Reactor& reactor_);
    };
}



#endif //ETBASE_TCPCONNECTOR_H
