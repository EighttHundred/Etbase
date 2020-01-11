//
// Created by eight on 1/7/20.
//

#include <cassert>
#include <arpa/inet.h>
#include <cstring>

#include "Sockaddr.h"
#include "Util.h"

//once set not change
Etbase::Sockaddr::Sockaddr(const sockaddr& addr_):
    addr(&addr_),ip(getIp(addr_)),port(getPort(addr_)) {
}

Etbase::Sockaddr::Sockaddr(const char *ip_, const char *port_):
    addr(getAddr(ip_,port_)),ip(ip_),port(port_){
}

sockaddr *Etbase::Sockaddr::getAddr(const char *ip_, const char *port_) {
    auto addr_=new sockaddr_in;
    bzero(addr_,len);
    if(ip!=nullptr)
        inet_pton(domain,ip_,&((sockaddr_in*)addr)->sin_addr);
    addr_->sin_family=domain;
    addr_->sin_port=htons(strToInt(port_));
    return (sockaddr*)addr_;
}

const char *Etbase::Sockaddr::getIp(const sockaddr& addr_) {
    auto ip_=new char[25];
    return inet_ntop(domain,&addr_,ip_,len);
}

char *Etbase::Sockaddr::getPort(const sockaddr& addr_) {
    auto port_=new char[10];
    return intToStr(ntohs(((sockaddr_in*)&addr_)->sin_port));
}

Etbase::Sockaddr::~Sockaddr() {
    delete(ip);
    delete(port);
    delete(addr);
}

Etbase::Sockaddr::Sockaddr(const Etbase::Sockaddr &sockaddr):
    addr(sockaddr.addr),ip(sockaddr.ip),port(sockaddr.port){
}

Etbase::Sockaddr &Etbase::Sockaddr::operator=(const Etbase::Sockaddr &sockaddr) {
    if(&sockaddr!=this){
        port=sockaddr.port;
        ip=sockaddr.ip;
        addr=sockaddr.addr;
    }
    return *this;
}



