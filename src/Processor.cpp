#include "../include/Processor.h"
using namespace Etbase;

void Processor::doRead(const Socket &sock,Buffer &buffer){
    int ret=sock.read(buffer);
    if(ret>0){
        doRead_G();
    }else if(ret==0){
        doRead_Z();
    }else if(ret<0){
        switch(errno){
            case EAGAIN:
                doRead_L_EAGAIN();
                break;
            case EINTR:
                break;
            case EPIPE:
                break;
            default:
                doRead_L();
                break;
        }
    }
}

void Processor::doWrite(const Socket &sock,const Buffer &buffer){
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

void Processor::doRead_Z(){
    std::cout<<"conn "<<conn.getFd()<<" closed\n";
    reactorPtr->remove(conn.getFd());
    conn.close();
}

void Processor::doRead_L_EAGAIN(){
    if(readCallback!= nullptr)
        readCallback(conn);
    std::cout<<"read later\n";
    reactorPtr->updateEvent(conn.getFd(),getReadConf());
    return;
}

void Processor::doRead_L(){
    std::cout<<"close ernno:"<<errno<<std::endl;
    reactorPtr->remove(conn.getFd());
    conn.close();
}