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
        EventConf connConf;
        Socket sendSock;
        EventConf sendConf;
        EventConf readConf;
        std::map<int,String> buffMap;
        Epoll* epollPtr;
        Reactor* reactorPtr;
        int userType=0;
        Handler connCallback=nullptr; //for listen socket
        Handler readCallback=nullptr; //for connect socket
        Handler sendCallback=nullptr; //for connect socket
        void handleConn();
        void handleRead(Socket conn);
        void handleSend(Socket sock);
        void handleTimer(Timer& timer_);
    public:
        ~TcpConnector();
        void setReadCallback(Handler callback);
        void setConnCallback(Handler callback);
        void setSendCallback(Handler callback);
        String& getBuff(int fd);
        void start();
        void initServer(const char* port);
        void initSender(const char* ip,const char* port,int times=1,int timeout=100,int delay=0);
        void setSendData(String& data);
        TcpConnector(Reactor& reactor);
    };
}



#endif //ETBASE_TCPCONNECTOR_H
