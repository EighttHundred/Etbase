//
// Created by eight on 3/1/20.
//

#ifndef ETBASE_TCPSERVER_H
#define ETBASE_TCPSERVER_H

#include <memory>
#include "Socket.h"
#include "Reactor.h"
namespace Etbase{
    class TcpServer {
    private:
        Socket listenSock;
        static Reactor* reactorPtr;
        static Handler connHandler;
        static Handler readHandler;
        static Handler writeHandler;
        static void handleConn(Socket conn);
        static void handleRead(Socket conn);
        static void handleWrite(Socket conn);
    public:
        static void setRead(Handler handler);
        static void setConn(Handler handler);
        static void setWrite(Handler handler);
        explicit TcpServer(const char* port);
        void assign(Reactor& reactor);
    };

}



#endif //ETBASE_TCPSERVER_H
