//
// Created by eight on 3/1/20.
//

#include <iostream>
#include <utility>
#include "TcpServer.h"


Etbase::TcpServer::TcpServer(const char *port){
    listenSock.bind(port);
    std::cout<<"listen:  "<<listenSock.listen()<<std::endl;
}

void Etbase::TcpServer::handleConn(Etbase::Socket listenSock) {
    Event event;
    Socket conn=listenSock.accept();
    if(conn.getFd()==-1){
        std::cout<<"accept error"<<std::endl;
        std::cout<<"errno: "<<errno<<std::endl;
        return;
    }else{
        std::cout<<"accept success\n";
        std::cout<<"fd:"<<conn.getFd()<<std::endl;
    }
    event.sock=conn;
    event.fd=conn.getFd();
    event.setCallback(std::bind(&TcpServer::handleRead,this,event.sock));
    event.eventType=listenSock.getConnType();
    reactorPtr->regist(event);
    if(connCallback!= nullptr) connCallback(conn);
}

void Etbase::TcpServer::handleRead(Etbase::Socket conn) {
    String& buff=getBuff(conn.getFd());
    int ret=conn.read(buff);
    if(ret==0){
        std::cout<<"conn "<<conn.getFd()<<" closed\n";
        conn.close();
    }else if(ret<0){
        if(errno==EAGAIN){
            std::cout<<"read later\n";
            reactorPtr->resetOneShot(conn.getFd());
        }else{
            std::cout<<"error..close\n";
            conn.close();
        }
    }
    if(readCallback!= nullptr) readCallback(conn);
}

void Etbase::TcpServer::handleWrite(Etbase::Socket conn) {
    if(writeCallback!= nullptr) writeCallback(conn);
}

void Etbase::TcpServer::assign(Etbase::Reactor& reactor) {
    reactorPtr=&reactor;
    Event event;
    event.fd=listenSock.getFd();
    event.sock=listenSock;
    event.setCallback(std::bind(&TcpServer::handleConn,this,event.sock));
    reactorPtr->regist(event);
}

void Etbase::TcpServer::setReadCallback(Etbase::Handler callback) {
    readCallback=std::move(callback);
}

void Etbase::TcpServer::setConnCallback(Etbase::Handler callback) {
    connCallback=std::move(callback);
}

void Etbase::TcpServer::setWriteCallback(Etbase::Handler callback) {
    writeCallback=std::move(callback);
}

Etbase::String &Etbase::TcpServer::getBuff(int fd) {
    return buffMap[fd];
}


