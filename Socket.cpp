//
// Created by eight on 1/7/20.
//

#include <arpa/inet.h>
#include "Socket.h"
#include <unistd.h>
#include <netinet/in.h>

ehd::Socket::Socket(const char *ip, const char *port):
    sock(new Sockaddr(ip,port)),
    fd(::socket(sock->domain,sock->type,sock->protocal)) {
}


ehd::Socket::Socket(int fd_, const ehd::Sockaddr *sock_):
        fd(fd_),sock(sock_){
}

ehd::Socket ehd::Socket::accept() {
    auto *sock_ = new sockaddr;
    int fd_=::accept(fd,sock_, nullptr);
    if(fd_!=-1) return Socket(fd_, new Sockaddr(sock_));
    else return nullptr;
}

bool ehd::Socket::listen(int num) {
    return ::listen(fd, num) ==0;
}

bool ehd::Socket::bind() {
    return ::bind(fd,sock->addr,sock->len)>=0;
}

bool ehd::Socket::connect(const Sockaddr& sock_) {
    return ::connect(fd,sock_.addr,sock->len)==0;
}

ehd::Socket::~Socket() {
    ::close(fd);
}
