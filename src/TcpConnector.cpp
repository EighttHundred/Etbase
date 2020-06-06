//
// Created by eighthundred on 2020/4/24.
//

#include "../include/TcpConnector.h"
#include <utility>

using namespace Etbase;


TcpConnector::~TcpConnector() {
}

void TcpConnector::setReadConf(const EventConf &conf){
    readConf=conf;
}

void TcpConnector::setWriteConf(const EventConf &conf){
    writeConf=conf;
}

void TcpConnector::setAcceptConf(const EventConf &conf){
    acceptConf=conf;
}

void TcpConnector::setConnHandler(Handler handler){
    processor.addHandler(0,handler);
}

void TcpConnector::setSenderHandler(Handler handler){
    processor.addHandler(sendSock.getFd(),handler);
}

void TcpConnector::start() {
    reactor.start();
}

void TcpConnector::initServer(const char *port) {
    if(!listenSock.bind(port)){
        std::cout<<"listen failed"<<std::endl;
        return;
    }
    std::cout<<"listen:  "<<listenSock.listen()<<std::endl;
    processor.addListenEvent(listenSock);
    auto conf=reactor.getConf();
    conf.canStop=false;
    reactor.setConf(conf);
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
    timer.setHandler(std::bind(&TcpConnector::handleTimer,this,timer));
    reactor.addTimer(timer);
}

TcpConnector::TcpConnector(Reactor &reactor_):reactor(reactor_),
    processor(reactor_.getAcceptor(),reactor_.getEventMap(),
    readConf,writeConf,acceptConf),bufferMap(reactor_.getBufferMap()){
    // reactor.setTimeout(1000);
}

void TcpConnector::handleTimer(Timer& timer_) {
    if(!timer_.isTriggered()){
        //for delay task
        processor.addWriteEvent(sendSock);
    }else{
        processor.updateEvent(sendSock.getFd(),writeConf);
    }
}

void TcpConnector::setSendData(const Buffer& data) {
    bufferMap[sendSock.getFd()]=std::make_shared<Buffer>(data);
}


