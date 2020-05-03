#include "../include/TcpProcessor.h"
using namespace Etbase;

void TcpProcessor::setReadConf(const EventConf &conf){
    readConf=conf;
}

void TcpProcessor::setWriteConf(const EventConf &conf){
    writeConf=conf;
}

void TcpProcessor::setAcceptConf(const EventConf &conf){
    acceptConf=conf;
}

void TcpProcessor::addHandler(int fd,bool in,Handler handler){
    handlerMap.insert(fd,in,handler);
}

void TcpProcessor::addReadHandler(int fd,Handler handler){
    handlerMap.insert(fd,true,handler);
}

void TcpProcessor::addWriteHandler(int fd,Handler handler){
    handlerMap.insert(fd,false,handler);
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
    auto connEventPtr=std::make_shared<Event>(conn,readConf);
    connEventPtr->setTask(std::bind(&TcpProcessor::doAccept,this,connEventPtr));
    eventMap.insert(connEventPtr);
    acceptor.add(connEventPtr);
}

void TcpProcessor::doRead(EventPtr eventPtr){
    auto buffer=eventPtr->getBuffer();
    auto sock=eventPtr->getSocket();
    int ret=sock.read(buffer);
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
    auto buffer=eventPtr->getBuffer();
    auto sock=eventPtr->getSocket();
    int ret=sock.write(buffer);
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
    auto task=handlerMap.get(eventPtr->fd,false);
    if(task){
        task(eventPtr);
    }
    std::cout<<eventPtr->getBuffer()<<std::endl;
}

void TcpProcessor::doRead_Z(EventPtr eventPtr){
    std::cout<<"conn "<<eventPtr->getSocket().getFd()<<" closed\n";
    acceptor.remove(eventPtr->getSocket().getFd());
    eventPtr->getSocket().close();
}

void TcpProcessor::doRead_L_EAGAIN(EventPtr eventPtr){
    auto task=handlerMap.get(eventPtr->fd,true);
    if(task){
        task(eventPtr);
    }
    std::cout<<"read later\n";
    acceptor.update(eventPtr->getSocket().getFd(),readConf);
}

void TcpProcessor::doRead_L(EventPtr eventPtr){
    std::cout<<"close ernno:"<<errno<<std::endl;
    acceptor.remove(eventPtr->getSocket().getFd());
    eventPtr->getSocket().close();
}