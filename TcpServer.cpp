//
// Created by eight on 3/1/20.
//

#include <iostream>
#include <utility>
#include "TcpServer.h"

std::map<int,Etbase::String> Etbase::TcpServer::buffMap;
Etbase::Reactor* Etbase::TcpServer::reactorPtr= nullptr;
Etbase::Handler Etbase::TcpServer::connHandler= nullptr;
Etbase::Handler Etbase::TcpServer::readHandler= nullptr;
Etbase::Handler Etbase::TcpServer::writeHandler= nullptr;

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
    event.handler=handleRead;
    event.eventType=listenSock.getConnType();
    reactorPtr->regist(event);
    if(connHandler!= nullptr) connHandler(conn);
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
    if(readHandler!= nullptr) readHandler(conn);
}

void Etbase::TcpServer::handleWrite(Etbase::Socket conn) {
    if(writeHandler!= nullptr) writeHandler(conn);
}

void Etbase::TcpServer::assign(Etbase::Reactor& reactor) {
    reactorPtr=&reactor;
    Event event;
    event.fd=listenSock.getFd();
    event.sock=listenSock;
    event.handler=handleConn;
    reactorPtr->regist(event);
}

void Etbase::TcpServer::setRead(Etbase::Handler handler) {
    readHandler=std::move(handler);
}

void Etbase::TcpServer::setConn(Etbase::Handler handler) {
    connHandler=std::move(handler);
}

void Etbase::TcpServer::setWrite(Etbase::Handler handler) {
    writeHandler=std::move(handler);
}

Etbase::String &Etbase::TcpServer::getBuff(int fd) {
    return buffMap[fd];
}

