//
// Created by eight on 3/1/20.
//

#ifndef ETBASE_TCPSERVER_H
#define ETBASE_TCPSERVER_H

#include <memory>
#include <map>
#include "Socket.h"
#include "Reactor.h"
namespace Etbase{
    class TcpServer {
    private:
        Socket listenSock;
        EventConf connConf;
        std::map<int,String> buffMap;
        Epoll* epollPtr;
        Reactor* reactorPtr;
        Handler connCallback=nullptr; //for listen socket
        Handler readCallback=nullptr; //for connect socket
        Handler writeCallback=nullptr; //for connect socket
        void handleConn(Socket conn);
        void handleRead(Socket conn);
        void handleWrite(Socket conn);
    public:
        ~TcpServer();
        void setReadCallback(Handler callback);
        void setConnCallback(Handler callback);
        void setWriteCallback(Handler callback);
        explicit TcpServer(const char* port);
        void assign(Reactor& reactor);
        String& getBuff(int fd);
        void registWrite(
    };

}



#endif //ETBASE_TCPSERVER_H
