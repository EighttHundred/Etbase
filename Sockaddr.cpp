//
// Created by eight on 1/7/20.
//

#include <cassert>
#include <arpa/inet.h>
#include <cstring>

#include "Sockaddr.h"
#include "Util.h"

//once set not change
Etbase::Sockaddr::Sockaddr(const sockaddr& addr_){
    addr=std::make_shared<sockaddr>(addr_);
    auto ip_=new char[25];
    ip=inet_ntop(domain,&addr_,ip_,len);
    port=intToStr(ntohs(((sockaddr_in*)&addr_)->sin_port));
}

Etbase::Sockaddr::Sockaddr(const char *ip_, const char *port_):
    ip(ip_),port(port_){
    auto addr_=new sockaddr_in;
    bzero(addr_,len);
    if(ip!=nullptr)
        inet_pton(domain,ip_,&addr_->sin_addr);
    addr_->sin_family=domain;
    addr_->sin_port=htons(strToInt(port_));
    addr=std::make_shared<sockaddr>(*(sockaddr*)addr_);
}

Etbase::Sockaddr::Sockaddr(const char *port_):
        addr(),ip(),port(port_){
}

Etbase::Sockaddr::~Sockaddr() =default;

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





