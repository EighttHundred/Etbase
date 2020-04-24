//
// Created by eight on 3/5/20.
//

#include "../include/TcpClient.h"
using namespace Etbase;

TcpClient::TcpClient(const char *ip, const char *port) {
    cliSock.connect(ip,port);
}

TcpClient::~TcpClient() {
    reactorPtr->remove(cliSock.getFd());
    cliSock.close();
}

void TcpClient::handleRead(Socket conn) {
    std::cout<<"read!"<<std::endl;
    int ret=conn.read(cliBuff);
//    if(ret==0){
//        std::cout<<"conn "<<conn.getFd()<<" closed\n";
//        reactorPtr->remove(conn.getFd());
//        conn.close();
//    }else if(ret<0){
//        if(errno==EAGAIN||errno==EWOULDBLOCK){
//            if(readCallback!= nullptr)
//                readCallback(conn);
//            std::cout<<"read later\n";
//            EventConf conf=cliConf;
//            epollPtr->update(conn.getFd(),conf);
//            return;
//        }else{
//            std::cout<<"close ernno:"<<errno<<std::endl;
//            reactorPtr->remove(conn.getFd());
//            conn.close();
//        }
//    }
}

void TcpClient::assign(Reactor &reactor) {
    reactorPtr=&reactor;
    epollPtr=reactorPtr->getPoller();
    Event event;
    event.fd=cliSock.getFd();
    event.conf=cliConf;
    event.setCallback(std::bind(&TcpClient::handleRead,this,event.sock));
    reactorPtr->regist(event);
    event.conf.in=false;
    event.setCallback(std::bind(&TcpClient::handleWrite,this,event.sock));
    reactorPtr->regist(event);
}

void TcpClient::handleWrite(Socket conn) {

}

void TcpClient::setReadCallback(Handler callback) {
    readCallback=callback;
}

void TcpClient::setWriteCallback(Handler callback) {
    writeCallback=callback;
}

String &TcpClient::getBuff() {
    return cliBuff;
}

int TcpClient::sendData(String &buff) {
    return buff.write(cliSock.getFd());
}
