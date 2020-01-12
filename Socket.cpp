//
// Created by eight on 1/7/20.
//

#include <arpa/inet.h>
#include "Socket.h"
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include <fcntl.h>
#include <netdb.h>
#include <iostream>

Etbase::Socket::Socket():
    fd(socket(domain,type,protocal)){
}

Etbase::Socket::Socket(int fd_):
        fd(fd_){
}

Etbase::Socket Etbase::Socket::accept(Etbase::Sockaddr &sock) {
    auto addr = new sockaddr;
    int fd_=::accept(fd,addr, &sock.len);
    if(fd_!=-1) sock=Sockaddr(*addr);
    else std::cout<<strerror(errno)<<std::endl;
    return fd_;
}

bool Etbase::Socket::listen(int num) {
    return ::listen(fd, num) ==0;
}

bool Etbase::Socket::bind(Etbase::Sockaddr &sock) {
    int on=-1;
    addrinfo hints={},*res,*ressave;
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags=AI_PASSIVE;
    if(getaddrinfo(nullptr,sock.port,&hints,&res)==0){
        ressave=res;
        do{
            if(setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))!=-1){
                if(::bind(fd,(sockaddr*)res->ai_addr,res->ai_addrlen)==0){
                    sockaddr_in* tmp=(sockaddr_in*)res->ai_addr;
                    sock=Sockaddr(*res->ai_addr);
                    freeaddrinfo(ressave);
                    return true;
                }
            }

        }while((res=res->ai_next)!=nullptr);
        freeaddrinfo(ressave);
    }
    return false;
}

bool Etbase::Socket::connect(const Sockaddr& sock) {
    return ::connect(fd,sock.addr.get(),sock.len)==0;
}

Etbase::Socket::~Socket() {
    close(fd);
}

bool Etbase::Socket::write(const char *data) {
    ssize_t left=strlen(data),len;
    auto now=data;
    while(left>0){
        len=::write(fd,now,left);
        if(len<=0){
            if(errno==EINTR&&len<0) len=0;
            else return false;
        }
        left-=len;
        now+=len;
    }
    return true;
}

int Etbase::Socket::read(char *buff,int size) {
    return ::read(fd,buff, size);
}

bool Etbase::Socket::setNonBlock() {
    int flags=fcntl(fd,F_GETFL,0);
    if(flags!=-1){
        flags |= O_NONBLOCK;
        if(fcntl(fd,F_SETFL,flags)!=-1) return true;
    }
    return false;
}











