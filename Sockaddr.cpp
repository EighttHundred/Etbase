//
// Created by eight on 1/7/20.
//

#include <cassert>
#include <arpa/inet.h>
#include <cstring>

#include "Sockaddr.h"
#include "Util.h"

//once set not change
ehd::Sockaddr::Sockaddr(const sockaddr *addr_):
    addr(addr_) {
}

ehd::Sockaddr::Sockaddr(const char *ip, const char *port):
    addr(getAddr(ip,port)){
}

sockaddr *ehd::Sockaddr::getAddr(const char *ip, const char *port) {
    auto addr_=new sockaddr_in;
    bzero(addr_,len);
    if(ip!=nullptr)
        inet_pton(domain,ip,&((sockaddr_in*)addr)->sin_addr);
    addr_->sin_family=domain;
    addr_->sin_port=htons(strToInt(port));
    return (sockaddr*)addr_;
}

