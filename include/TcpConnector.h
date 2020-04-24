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
        bool isSender=false;
        bool isServer=false;
        Socket listenSock;
        EventConf connConf;
        Socket sendSock;
        EventConf sendConf;
        Timer timer;
        String sendBuff;
        std::map<int,String> buffMap;
        Epoll* epollPtr;
        Reactor* reactorPtr;
        Handler connCallback=nullptr; //for listen socket
        Handler readCallback=nullptr; //for connect socket
        Handler sendCallback=nullptr; //for connect socket
        void handleConn(Socket listenSock_);
        void handleRead(Socket conn);
        void handleSend(Socket sendSock_);
    public:
        ~TcpConnector();
        void setReadCallback(Handler callback);
        void setConnCallback(Handler callback);
        void setSendCallback(Handler callback);
        String& getBuff(int fd);
        void run();
        void assign(Reactor& reactor);
        void initServer(const char* port);
        void initSender(const char* ip,const char* port,int times=1,int timeout=100,int delay=0);
    };
}



#endif //ETBASE_TCPCONNECTOR_H
