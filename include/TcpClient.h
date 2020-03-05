//
// Created by eight on 3/5/20.
//

#ifndef ETBASE_TCPCLIENT_H
#define ETBASE_TCPCLIENT_H

#include "Event.h"
#include "Reactor.h"

namespace Etbase{
    class TcpClient {
    private:
        Socket cliSock;
        EventConf cliConf;
        String cliBuff;
        Epoll* epollPtr;
        Reactor* reactorPtr;
        Handler readCallback=nullptr;
        Handler writeCallback=nullptr;
        void handleRead(Socket conn);
        void handleWrite(Socket conn);

    public:
        TcpClient(const char* ip,const char* port);
        ~TcpClient();
        void setReadCallback(Handler callback);
        void setWriteCallback(Handler callback);
        void assign(Reactor& reactor);
        String& getBuff();
        int sendData(String& buff);
    };
}



#endif //ETBASE_TCPCLIENT_H
