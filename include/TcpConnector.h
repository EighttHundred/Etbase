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
namespace Etbase{
    class TcpConnector {
    private:
        Socket listenSock;
        Socket sendSock;
        Reactor* reactorPtr;
        Handler connCallback=nullptr; //for listen socket
        Handler readCallback=nullptr; //for connect socket
        EventConf getReadConf();
        EventConf getWriteConf();
        void handleConn();
        void handleRead(Socket &conn,Buffer &buffer);
        void handleSend(Socket &sock,Buffer &data);
        void handleTimer(Timer& timer_);
        void setCallback(int fd,bool in,Handler callback);
    public:
        ~TcpConnector();
        void setReadCallback(Handler callback);
        void setConnCallback(Handler callback);
        void start();
        void initServer(const char* port);
        void initSender(const char* ip,const char* port,int times=1,int timeout=100,int delay=0);
        void setSendData(const Buffer& data);
        TcpConnector(Reactor& reactor);
    };
}



#endif //ETBASE_TCPCONNECTOR_H
