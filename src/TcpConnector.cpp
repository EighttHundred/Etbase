//
// Created by eighthundred on 2020/4/24.
//

#include "../include/TcpConnector.h"
#include <utility>

using namespace Etbase;


TcpConnector::~TcpConnector() {
}

void TcpConnector::setConnHandler(Handler handler){
    specifyHandlerMap[0]=handler;
}

void TcpConnector::setSenderHandler(Handler handler){
    specifyHandlerMap[sendSock.getFd()]=handler;
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
    addEvent(listenSock,acceptConf);
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
    timer.setTask(std::bind(&TcpConnector::doTimer,this,timer));
    reactor.addTimer(timer);
}

TcpConnector::TcpConnector(Reactor &reactor_):reactor(reactor_){
    // reactor.setTimeout(1000);
    writeConf.in=false;
    writeConf.oneshot=true;
    readConf.oneshot=true;
}

void TcpConnector::doTimer(Timer& timer_) {
    if(!timer_.isTriggered()){
        //for delay task
        addEvent(sendSock,writeConf);
    }else{
        reactor.getAcceptor().update(sendSock.getFd(),writeConf);
    }
}

void TcpConnector::setSendData(const Buffer& data) {
    reactor.getBufferMap()[sendSock.getFd()]=std::make_shared<Buffer>(data);
}

void TcpConnector::doAccept(EventPtr eventPtr,BufferPtr bufferPtr){
    auto listenSock=eventPtr->getSocket();
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
    specifyHandlerMap[conn.getFd()]=specifyHandlerMap[0];
    addEvent(conn,readConf);
}

void TcpConnector::doRead(EventPtr eventPtr,BufferPtr bufferPtr){
    int fd=eventPtr->fd;
    auto sock=eventPtr->getSocket();
    int ret=sock.read(bufferPtr);
    if(ret>0){
        // not yet complete
    }else if(ret==0){
        std::cout<<"conn "<<eventPtr->getSocket().getFd()<<" closed\n";
        reactor.getAcceptor().remove(eventPtr->getSocket().getFd());
        eventPtr->getSocket().close();
    }else if(ret<0){
        switch(errno){
            case EAGAIN:
                if(specifyHandlerMap.find(fd)!=specifyHandlerMap.end()){
                    specifyHandlerMap[fd](eventPtr,bufferPtr);
                }
                std::cout<<"read later\n";
                reactor.getAcceptor().update(eventPtr->getSocket().getFd(),eventPtr->conf);
                break;
            case EINTR:
                break;
            case EPIPE:
                break;
            default:
                std::cout<<"close ernno:"<<errno<<std::endl;
                reactor.getAcceptor().remove(eventPtr->getSocket().getFd());
                eventPtr->getSocket().close();
                break;
        }
    }
}

void TcpConnector::doWrite(EventPtr eventPtr,BufferPtr bufferPtr){
    int fd=eventPtr->fd;
    auto sock=eventPtr->getSocket();
    int ret=sock.write(*bufferPtr);
    if(ret>0){
        // not yet complete
    }else if(ret<0){
        switch(errno){
            case EAGAIN:
                std::cout << "write later\n";
                // epollPtr->update(conn.getFd(),readConf);
                break;
            default:
                std::cout<<"close ernno:"<<errno<<std::endl;
                reactor.getAcceptor().remove(eventPtr->fd);
                eventPtr->getSocket().close();
                break;
        }
    }else if(ret==0){
        if(specifyHandlerMap.find(fd)!=specifyHandlerMap.end()){
            specifyHandlerMap[fd](eventPtr,bufferPtr);
        }
    }   
}

void TcpConnector::addEvent(Socket socket,EventConf eventConf){
    auto readEventPtr=std::make_shared<Event>(socket,eventConf);
    reactor.getEventMap()[socket.getFd()]=readEventPtr;
    if(reactor.getBufferMap().find(socket.getFd())==reactor.getBufferMap().end()){
        reactor.getBufferMap()[socket.getFd()]=std::make_shared<Buffer>();
    }
    if(socket.getFd()==listenSock.getFd()){
        reactor.getTaskMap()[socket.getFd()]=std::bind(&TcpConnector::doAccept,this,readEventPtr,reactor.getBufferMap()[socket.getFd()]);
    }else if(socket.getFd()==sendSock.getFd()){
        reactor.getTaskMap()[socket.getFd()]=std::bind(&TcpConnector::doWrite,this,readEventPtr,reactor.getBufferMap()[socket.getFd()]);
    }else{
        reactor.getTaskMap()[socket.getFd()]=std::bind(&TcpConnector::doRead,this,readEventPtr,reactor.getBufferMap()[socket.getFd()]);
    }
    reactor.getAcceptor().add(readEventPtr);
}