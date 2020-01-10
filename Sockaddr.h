//
// Created by eight on 1/7/20.
//

#ifndef NET_SOCKADDR_H
#define NET_SOCKADDR_H


#include <bits/socket.h>
#include <netinet/in.h>
namespace ehd{
    class Sockaddr {
    public:
        int domain=AF_INET;
        int type=SOCK_STREAM;
        int protocal=0;
        const sockaddr*const addr;
        socklen_t len= sizeof(sockaddr_in);
    public:
        explicit Sockaddr(const sockaddr* addr_);
        Sockaddr(const char* ip,const char* port);
    private:
        sockaddr* getAddr(const char* ip,const char* port);
    };

}


#endif //NET_SOCKADDR_H
