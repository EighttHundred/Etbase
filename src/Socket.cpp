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

Etbase::Socket Etbase::Socket::accept() const{
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


int Etbase::Socket::write(const Buffer& data) const{
    int ret;
    int now=0;
    while((ret=::write(fd,data.begin()+now,data.size()-now))>0){
        now+=ret;
    }
    return ret;
}

int Etbase::Socket::read(BufferPtr buff) const{
    int ret;
    while((ret=::read(fd,buff->end(),buff->spare()))>0){
        buff->append(ret);
    }
    return ret;
}

bool Etbase::Socket::close() const{
    return ::close(fd)==0;
}

bool Etbase::Socket::connect(const char *ip_, const char *port_) {
    if(ip_== nullptr||port_== nullptr) return false;
    port=port_;
    auto ip_net=gethostbyname(ip_)->h_addr_list[0];
    if(ip_net== nullptr) return false;
    ip=inet_ntoa(*(struct in_addr*)ip_net);
    if(inet_pton(domain,ip,&addr.sin_addr)<=0) return false;
    addr.sin_port=htons(strToInt(port_));
    addr.sin_family=domain;
    return ::connect(fd,(sockaddr*)&addr,socklen)==0;
}

int Etbase::Socket::getFd() const{
    return fd;
}

bool Etbase::Socket::setNonBlock(bool val) {
    int flags=fcntl(fd,F_GETFL,0);
    if(val) flags|=O_NONBLOCK;
    else if(flags&O_NONBLOCK) flags^=O_NONBLOCK;
    return fcntl(fd,F_SETFL,flags)!=-1;
}














