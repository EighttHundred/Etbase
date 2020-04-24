//
// Created by eight on 3/1/20.
//

#include <iostream>
#include <utility>
#include "../include/TcpServer.h"
#include <unistd.h>
using namespace Etbase;

TcpServer::TcpServer(const char *port){
    connConf.oneshot=true;
    connConf.et=true;
    connConf.in=true;
    listenSock.bind(port);
    std::cout<<"listen:  "<<listenSock.listen()<<std::endl;
}

void TcpServer::handleConn(Socket listenSock_) {
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

void TcpServer::handleRead(Socket conn) {
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
            EventConf conf=connConf;
            epollPtr->update(conn.getFd(),conf);
            return;
        }else{
            std::cout<<"close ernno:"<<errno<<std::endl;
            reactorPtr->remove(conn.getFd());
            conn.close();
        }
    }
}

void TcpServer::handleWrite(Socket conn) {
    if(writeCallback!= nullptr) writeCallback(conn);
}

void TcpServer::assign(Reactor& reactor) {
    reactorPtr=&reactor;
    epollPtr=reactor.getPoller();
    Event event;
    event.fd=listenSock.getFd();
    event.sock=listenSock;
    event.setCallback(std::bind(&TcpServer::handleConn,this,event.sock));
    reactorPtr->regist(event);
}

void TcpServer::setReadCallback(Handler callback) {
    readCallback=callback;
}

void TcpServer::setConnCallback(Handler callback) {
    connCallback=callback;
}

void TcpServer::setWriteCallback(Handler callback) {
    writeCallback=callback;
}

String &TcpServer::getBuff(int fd) {
    return buffMap[fd];
}

TcpServer::~TcpServer() {
    reactorPtr->remove(listenSock.getFd());
    listenSock.close();
}

void TcpServer::run(int times) {
    reactorPtr->loop();
}




