//
// Created by eighthundred on 2020/4/24.
//

#include "../include/TcpConnector.h"

#include <utility>

using namespace Etbase;

EventConf TcpConnector::getReadConf(){
    return getConfigedConf(true,true,true,false);
}

EventConf TcpConnector::getWriteConf(){
    return getConfigedConf(true,true,false,false);
}


void TcpConnector::handleConn() {
    Socket conn=listenSock.accept();
    if(conn.getFd()==-1){
        std::cout<<"accept error"<<std::endl;
        std::cout<<"errno: "<<errno<<std::endl;
        return;
    }else{
        std::cout<<"accept success\n";
        std::cout<<"fd:"<<conn.getFd()<<std::endl;
    }
    conn.setNonBlock(true);
    Event event(conn,getReadConf(),std::bind(&TcpConnector::handleRead,this,conn));
    reactorPtr->addEvent(event);
    if(connCallback!= nullptr) connCallback(conn);
}

void TcpConnector::handleRead(Socket conn) {
    String buff=getBuff(conn.getFd());
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
            epollPtr->update(conn.getFd(),getReadConf());
            return;
        }else{
            std::cout<<"close ernno:"<<errno<<std::endl;
            reactorPtr->remove(conn.getFd());
            conn.close();
        }
    }
}

void TcpConnector::handleSend(Socket sock) {
    String buffer= getBuff(sendSock.getFd());
    int ret=sock.write(buffer);
    if(ret>0){
        return;
        //        std::cout<<"conn "<<conn.getFd()<<" closed\n";
//        reactorPtr->remove(conn.getFd());
//        conn.close();
    }else if(ret<0){
        if(errno==EAGAIN||errno==EWOULDBLOCK) {
            std::cout << "write later\n";
//            epollPtr->update(conn.getFd(),readConf);
            return;
        }else if(errno==EINTR) {
//            std::cout<<""
        }else if(errno==EPIPE) {

        }else{
            std::cout<<"close ernno:"<<errno<<std::endl;
            reactorPtr->remove(sendSock.getFd());
            sendSock.close();
        }
    }else{
//        std::cout<<buff<<std::endl;
        if(sendCallback!= nullptr) sendCallback(sendSock);
    }
}

TcpConnector::~TcpConnector() {
    //not close if child thread is still working
//    if(userType&1){
//        reactorPtr->remove(sendSock.getFd());
//        sendSock.close();
//    }
//    if(userType&2){
//        reactorPtr->remove(listenSock.getFd());
//        listenSock.close();
//    }
}

void TcpConnector::setReadCallback(Handler callback) {
    readCallback=std::move(callback);
}

void TcpConnector::setConnCallback(Handler callback) {
    connCallback=std::move(callback);
}

void TcpConnector::setSendCallback(Handler callback) {
    sendCallback=std::move(callback);
}

String TcpConnector::getBuff(int fd) {
    return bufferMap.getBuffer(fd);
}

void TcpConnector::start() {
    reactorPtr->start();
}

void TcpConnector::initServer(const char *port) {
    if(!listenSock.bind(port)){
        std::cout<<"listen failed"<<std::endl;
        return;
    }
    std::cout<<"listen:  "<<listenSock.listen()<<std::endl;
    Event event(listenSock,getReadConf(),std::bind(&TcpConnector::handleRead,this,listenSock));
    reactorPtr->addEvent(event);
    auto conf=reactorPtr->getConf();
    conf.canStop=false;
    reactorPtr->setConf(conf);
}

void TcpConnector::initSender(const char *ip, const char *port, int times, int timeout,int delay) {
    if(!sendSock.connect(ip,port)){
        std::cout<<"connect failed"<<std::endl;
        return;
    }
    Timer timer;
    timer.setDelay(delay);
    timer.setTimes(times);
    timer.setTimeout(timeout);
    timer.setTask(std::bind(&TcpConnector::handleTimer,this,timer));
    reactorPtr->addTimer(timer);
}

TcpConnector::TcpConnector(Reactor &reactor) {
    reactorPtr=&reactor;
    epollPtr=reactor.getPoller();
    reactorPtr->setTimeout(1000);
}

void TcpConnector::handleTimer(Timer& timer_) {
    if(!timer_.isTriggered()){
        //for delay task
        Event event(sendSock,getReadConf(),std::bind(&TcpConnector::handleRead,this,sendSock));
        event.setCallback(std::bind(&TcpConnector::handleSend,this,sendSock));
        reactorPtr->addEvent(event);
    }else{
        epollPtr->update(sendSock.getFd(),getWriteConf());
    }
}

void TcpConnector::setSendData(const String& data) {
    bufferMap.insert(sendSock.getFd(),data);
}


void TcpConnector::setCallback(int fd,bool in,Handler callback){
    
}
