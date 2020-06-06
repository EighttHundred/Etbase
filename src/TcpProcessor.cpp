#include "../include/TcpProcessor.h"
using namespace Etbase;

TcpProcessor::TcpProcessor(Epoll &acceptor,
        EventMap &eventMap,
        BufferMap &bufferMap,
        HandlerMap &taskMap,
        EventConf &readConf,
        EventConf &writeConf,
        EventConf &acceptConf):
    acceptor(acceptor),eventMap(eventMap),readConf(readConf),
    writeConf(writeConf),acceptConf(acceptConf),
    bufferMap(bufferMap),taskMap(taskMap){
    writeConf.in=false;
}

void TcpProcessor::updateEvent(int fd,EventConf conf){
    acceptor.update(fd,conf);
}

void TcpProcessor::addListenEvent(const Socket &socket){
    int fd=socket.getFd();
    auto listenEventPtr=std::make_shared<Event>(socket,acceptConf);
    taskMap[fd]=std::bind(&TcpProcessor::doAccept,this,listenEventPtr);
    eventMap[fd]=listenEventPtr;
    acceptor.add(listenEventPtr);
}

void TcpProcessor::addReadEvent(const Socket &socket){
    int fd=socket.getFd();
    auto readEventPtr=std::make_shared<Event>(socket,readConf);
    
    taskMap[fd]=std::bind(&TcpProcessor::doRead,this,readEventPtr,eventMap[fd]);
    eventMap[fd]=readEventPtr;
    acceptor.add(readEventPtr);
}

void TcpProcessor::addWriteEvent(const Socket &socket){
    int fd=socket.getFd();
    auto writeEventPtr=std::make_shared<Event>(socket,writeConf);
    eventMap[fd]=writeEventPtr;
    taskMap[fd]=std::bind(&TcpProcessor::doWrite,this,writeEventPtr);
    acceptor.add(writeEventPtr);
}

void TcpProcessor::addHandler(int fd,Handler handler){
    taskMap[fd]=handler;
}

void TcpProcessor::doAccept(EventPtr eventPtr){
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
    addReadEvent(conn);
}

void TcpProcessor::doRead(EventPtr eventPtr){
    int fd=eventPtr->fd;
    auto buffer=bufferMap[fd];
    auto sock=eventPtr->getSocket();
    int ret=sock.read(*buffer);
    if(ret>0){
        doRead_G(eventPtr);
    }else if(ret==0){
        doRead_Z(eventPtr);
    }else if(ret<0){
        switch(errno){
            case EAGAIN:
                doRead_L_EAGAIN(eventPtr);
                break;
            case EINTR:
                break;
            case EPIPE:
                break;
            default:
                doRead_L(eventPtr);
                break;
        }
    }
}

void TcpProcessor::doWrite(EventPtr eventPtr){
    int fd=eventPtr->fd;
    auto bufferPtr=bufferMap[fd];
    auto sock=eventPtr->getSocket();
    int ret=sock.write(*bufferPtr);
    if(ret>0){
        doWrite_G(eventPtr);
    }else if(ret<0){
        switch(errno){
            case EAGAIN:
                doWrite_L_EAGAIN(eventPtr);
                break;
            default:
                doWrite_L(eventPtr);
                break;
        }
    }else if(ret==0){
        doWrite_Z(eventPtr);
    }
}

void TcpProcessor::doWrite_L(EventPtr eventPtr){
    std::cout<<"close ernno:"<<errno<<std::endl;
    acceptor.remove(eventPtr->fd);
    eventPtr->getSocket().close();
}

void TcpProcessor::doWrite_L_EAGAIN(EventPtr eventPtr){
    std::cout << "write later\n";
    // epollPtr->update(conn.getFd(),readConf);
}

void TcpProcessor::doWrite_Z(EventPtr eventPtr){
    int fd=eventPtr->fd;
    if(taskMap.find(fd)!=taskMap.end()){
        taskMap[fd](eventPtr,bufferMap[fd]);
    }
}

void TcpProcessor::doRead_Z(EventPtr eventPtr){
    std::cout<<"conn "<<eventPtr->getSocket().getFd()<<" closed\n";
    acceptor.remove(eventPtr->getSocket().getFd());
    eventPtr->getSocket().close();
}

void TcpProcessor::doRead_L_EAGAIN(EventPtr eventPtr){
    int fd=eventPtr->fd;
    if(taskMap.find(fd)!=taskMap.end()){
        taskMap[fd](eventPtr,bufferMap[fd]);
    }
    std::cout<<"read later\n";
    updateEvent(eventPtr->getSocket().getFd(),eventPtr->conf);
}

void TcpProcessor::doRead_L(EventPtr eventPtr){
    std::cout<<"close ernno:"<<errno<<std::endl;
    acceptor.remove(eventPtr->getSocket().getFd());
    eventPtr->getSocket().close();
}

void TcpProcessor::doRead_G(EventPtr eventPtr){

}

void TcpProcessor::doWrite_G(EventPtr eventPtr){

}
