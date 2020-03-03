//
// Created by eight on 3/1/20.
//

#include <iostream>
#include <utility>
#include "../include/TcpServer.h"
#include <unistd.h>

Etbase::TcpServer::TcpServer(const char *port){
    connConf.oneshot=true;
    connConf.et=true;
    connConf.eventType=EPOLLIN;
    listenSock.bind(port);
    std::cout<<"listen:  "<<listenSock.listen()<<std::endl;
}

void Etbase::TcpServer::handleConn(Etbase::Socket listenSock_) {
    Event event;
    Socket conn=listenSock_.accept();
    if(conn.getFd()==-1){
        std::cout<<"accept error"<<std::endl;
        std::cout<<"errno: "<<errno<<std::endl;
        return;
    }else{
        std::cout<<"accept success\n";
        std::cout<<"fd:"<<conn.getFd()<<std::endl;
    }
    conn.setNonBlock(true);
    event.conf=connConf;
    event.sock=conn;
    event.fd=conn.getFd();
    event.setCallback(std::bind(&TcpServer::handleRead,this,event.sock));
    reactorPtr->regist(event);
    if(connCallback!= nullptr) connCallback(conn);
}

void Etbase::TcpServer::handleRead(Etbase::Socket conn) {
    String& buff=getBuff(conn.getFd());
    int ret=conn.read(buff);
    if(ret==0){
        std::cout<<"conn "<<conn.getFd()<<" closed\n";
        reactorPtr->remove(conn.getFd());
        conn.close();
    }else if(ret<0){
        if(errno==EAGAIN||errno==EWOULDBLOCK){
            if(readCallback!= nullptr)
                readCallback(conn);
            std::cout<<"read later\n";
            connConf.eventType=EPOLLET|EPOLLONESHOT|EPOLLIN;
            epollPtr->update(conn.getFd(),connConf);
            return;
        }else{
            std::cout<<"error..close\n";
            reactorPtr->remove(conn.getFd());
            conn.close();
        }
    }
}

void Etbase::TcpServer::handleWrite(Etbase::Socket conn) {
    if(writeCallback!= nullptr) writeCallback(conn);
}

void Etbase::TcpServer::assign(Etbase::Reactor& reactor) {
    reactorPtr=&reactor;
    epollPtr=reactor.getPoller();
    Event event;
    event.fd=listenSock.getFd();
    event.sock=listenSock;
    event.setCallback(std::bind(&TcpServer::handleConn,this,event.sock));
    reactorPtr->regist(event);
}

void Etbase::TcpServer::setReadCallback(Etbase::Handler callback) {
    readCallback=callback;
}

void Etbase::TcpServer::setConnCallback(Etbase::Handler callback) {
    connCallback=callback;
}

void Etbase::TcpServer::setWriteCallback(Etbase::Handler callback) {
    writeCallback=callback;
}

Etbase::String &Etbase::TcpServer::getBuff(int fd) {
    return buffMap[fd];
}

Etbase::TcpServer::~TcpServer() {
    listenSock.close();
}

namespace Etbase{


}


