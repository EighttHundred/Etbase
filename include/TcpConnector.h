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
        TcpProcessor processor;
        Socket listenSock;
        Socket sendSock;
        Reactor* reactorPtr;
        void handleTimer(Timer& timer_);
    public:
        ~TcpConnector();
        void setConnReadTask(Handler handler);
        void setSenderReadTask(Handler handler);
        void setSenderWriteTask(Handler handler);
        void start();
        void initServer(const char* port);
        void initSender(const char* ip,const char* port,int times=1,int timeout=100,int delay=0);
        void setSendData(const Buffer& data);
        TcpConnector(Reactor& reactor);
    };
}



#endif //ETBASE_TCPCONNECTOR_H
