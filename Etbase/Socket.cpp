//
// Created by eight on 1/7/20.
//

#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include <netdb.h>
#include <fcntl.h>
#include <iostream>
#include "../include/Socket.h"
#include "../include/Util.h"

Etbase::Socket::Socket(){
    fd=socket(domain,type,protocal);
}

Etbase::Socket::Socket(int fd_,sockaddr_in& addr_){
    fd=fd_;
    addr=addr_;
    auto ip_=new char[25];
    ip=inet_ntop(domain,&addr_,ip_,socklen);
    port=intToStr(ntohs(((sockaddr_in*)&addr_)->sin_port));
}

Etbase::Socket Etbase::Socket::accept() {
    struct sockaddr_in addr_{};
    int fd_=::accept(fd,(sockaddr*)&addr_,(socklen_t*)&socklen);
    return Socket(fd_,addr_);
}

bool Etbase::Socket::listen(int num) {
    return ::listen(fd, num) ==0;
}

bool Etbase::Socket::bind(const char* port_) {
    port=port_;
    int on=-1;
    addrinfo hints={},*res,*ressave;
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags=AI_PASSIVE;
    if(getaddrinfo(nullptr,port,&hints,&res)==0){
        ressave=res;
        do{
            if(setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))!=-1){
                if(::bind(fd,(sockaddr*)res->ai_addr,res->ai_addrlen)==0){
                    char ip_[25];
                    addr=*((sockaddr_in*)res->ai_addr);
                    ip=inet_ntop(domain,&addr,ip_,socklen);
                    freeaddrinfo(ressave);
                    return true;
                }
            }

        }while((res=res->ai_next)!=nullptr);
        freeaddrinfo(ressave);
    }
    return false;
}


int Etbase::Socket::write(const String& data,long len) {
    int ret,now=0;
    while((ret=::write(fd,data.begin()+now,len-now))>0)
        now+=ret;
    return ret;
}

int Etbase::Socket::read(String& data) {
    int ret;
    while((ret=::read(fd,data.end(),data.spare()))>0)
        data.append(ret);
    return ret;
}

bool Etbase::Socket::close() {
    return ::close(fd)==0;
}

bool Etbase::Socket::connect(const char *ip_, const char *port_) {
    ip=ip_;
    port=port_;
    if(ip!=nullptr)
        inet_pton(domain,ip_,&addr.sin_addr);
    addr.sin_family=domain;
    addr.sin_port=htons(strToInt(port_));
    return ::connect(fd,(sockaddr*)&addr,socklen)==0;
}

int Etbase::Socket::getFd() {
    return fd;
}

bool Etbase::Socket::setNonBlock(bool val) {
    int flags=fcntl(fd,F_GETFL,0);
    if(val) flags|=O_NONBLOCK;
    else if(flags&O_NONBLOCK) flags^=O_NONBLOCK;
    return fcntl(fd,F_SETFL,flags)!=-1;
}














