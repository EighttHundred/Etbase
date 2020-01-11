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

Etbase::Socket::Socket(int fd_):
        fd(fd_){
}

Etbase::Socket Etbase::Socket::accept(Etbase::Sockaddr &addr) {
    auto *addr_ = new sockaddr;
    int fd_=::accept(fd,addr_, nullptr);
    if(fd_!=-1) addr=Sockaddr(*addr_);
    return fd_;
}

bool Etbase::Socket::listen(int num) {
    return ::listen(fd, num) ==0;
}

bool Etbase::Socket::bind(Etbase::Sockaddr &sock) {
//    return ::bind(fd,sock.addr,sock.len)>=0;
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
                    sock.addr=res->ai_addr;
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
    return ::connect(fd,sock.addr,sock.len)==0;
}

Etbase::Socket::~Socket() {
    close(fd);
}

int Etbase::Socket::write(const char *data) {
    return ::write(fd,data,strlen(data));
}

int Etbase::Socket::read(char *buff) {
    return ::read(fd,buff, sizeof(buff));
}

bool Etbase::Socket::setNonBlock() {
    int flags=fcntl(fd,F_GETFL,0);
    if(flags!=-1){
        flags |= O_NONBLOCK;
        if(fcntl(fd,F_SETFL,flags)!=-1) return true;
    }
    return false;
}





