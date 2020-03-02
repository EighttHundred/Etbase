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
        std::map<int,String> buffMap;
        Reactor* reactorPtr;
        Handler connCallback=nullptr;
        Handler readCallback=nullptr;
        Handler writeCallback=nullptr;
        void handleConn(Socket conn);
        void handleRead(Socket conn);
        void handleWrite(Socket conn);
    public:
        void setReadCallback(Handler callback);
        void setConnCallback(Handler callback);
        void setWriteCallback(Handler callback);
        explicit TcpServer(const char* port);
        void assign(Reactor& reactor);
        String& getBuff(int fd);
    };

}



#endif //ETBASE_TCPSERVER_H
