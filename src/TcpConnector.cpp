//
// Created by eighthundred on 2020/4/24.
//

#include "../include/TcpConnector.h"
#include <utility>

using namespace Etbase;


TcpConnector::~TcpConnector() {
}

void TcpConnector::setConnReadTask(Handler handler){

}

void TcpConnector::setSenderReadTask(Handler handler){
    
}

void TcpConnector::setSenderWriteTask(Handler handler){
    
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
    
    // Event event(listenSock,getReadConf(),std::bind(&TcpConnector::handleRead,this,listenSock));
    // reactorPtr->addEvent(event);
    // auto conf=reactorPtr->getConf();
    // conf.canStop=false;
    // reactorPtr->setConf(conf);
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
    // reactorPtr->setTimeout(1000);
}

void TcpConnector::handleTimer(Timer& timer_) {
    if(!timer_.isTriggered()){
        //for delay task
        Event event(sendSock,getReadConf());
        event.setTask(std::bind(&TcpConnector::handleRead,this,sendSock));
        reactorPtr->addEvent(event);
    }else{
        reactorPtr->updateEvent(sendSock.getFd(),getWriteConf());
    }
}

void TcpConnector::setSendData(const Buffer& data) {
    auto evptr=reactorPtr->getEvent(sendSock.getFd(),0);
    if(evptr!=nullptr){
        evptr->setBuffer(data);
    }
}


