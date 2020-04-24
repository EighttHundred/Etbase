//
// Created by eighthundred on 2020/4/24.
//

#include "../include/TcpConnector.h"

using namespace Etbase;

void TcpConnector::handleConn(Socket listenSock_) {
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
    event.setCallback(std::bind(&TcpConnector::handleRead,this,event.sock));
    reactorPtr->regist(event);
    if(connCallback!= nullptr) connCallback(conn);
}

void TcpConnector::handleRead(Socket conn) {
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
            epollPtr->update(conn.getFd(),readConf);
            return;
        }else{
            std::cout<<"close ernno:"<<errno<<std::endl;
            reactorPtr->remove(conn.getFd());
            conn.close();
        }
    }
}

void TcpConnector::handleSend(Socket sendSock_) {
    if(sendCallback!= nullptr) sendCallback(sendSock_);
}

TcpConnector::~TcpConnector() {
    if(userType&1){
        reactorPtr->remove(sendSock.getFd());
        sendSock.close();
    }
    if(userType&2){
        reactorPtr->remove(listenSock.getFd());
        listenSock.close();
    }
}

void TcpConnector::setReadCallback(Handler callback) {
    readCallback=callback;
}

void TcpConnector::setConnCallback(Handler callback) {
    connCallback=callback;
}

void TcpConnector::setSendCallback(Handler callback) {
    sendCallback=callback;
}

String &TcpConnector::getBuff(int fd) {
    return buffMap[fd];
}

void TcpConnector::run() {
    reactorPtr->start();
}

void TcpConnector::initServer(const char *port) {
    if(!listenSock.bind(port)){
        std::cout<<"listen failed"<<std::endl;
        return;
    }
    std::cout<<"listen:  "<<listenSock.listen()<<std::endl;
    Event event;
    event.fd=listenSock.getFd();
    event.sock=listenSock;
    event.setCallback(std::bind(&TcpConnector::handleConn,this,event.sock));
    userType|=2;
    reactorPtr->setUserType(userType);
    reactorPtr->regist(event);
}

void TcpConnector::initSender(const char *ip, const char *port, int times, int timeout,int delay) {
    if(!sendSock.connect(ip,port)){
        std::cout<<"connect failed"<<std::endl;
        return;
    }
    timer.setDelay(delay);
    timer.setTimes(times);
    timer.setTimeout(timeout);
    reactorPtr->initTimer(&timer);
    Event event;
    event.conf.in=false;
    event.fd=sendSock.getFd();
    event.sock=sendSock;
    event.conf=sendConf;
    event.setCallback(std::bind(&TcpConnector::handleRead,this,event.sock));
    userType|=1;
    reactorPtr->setUserType(userType);
    reactorPtr->regist(event);
}

TcpConnector::TcpConnector(Reactor &reactor) {
    connConf.oneshot=true;
    connConf.et=true;
    connConf.in=true;
    readConf.in=true;
    readConf.oneshot=true;
    readConf.et=true;
    sendConf.in=false;
    sendConf.et=true;
    sendConf.oneshot=true;
    reactorPtr=&reactor;
    epollPtr=reactor.getPoller();
    reactorPtr->init(100);
}

void TcpConnector::handleTimer(int fd) {
    epollPtr->update(fd,sendConf);
}


