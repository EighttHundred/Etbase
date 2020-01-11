//
// Created by eight on 1/7/20.
//

#ifndef ETBASE_SOCKADDR_H
#define ETBASE_SOCKADDR_H


#include <bits/socket.h>
#include <netinet/in.h>
namespace Etbase{
    class Sockaddr {
    public:
        const int domain=AF_INET;
        const int type=SOCK_STREAM;
        const int protocal=0;
        const char* port;
        const char* ip;
        const sockaddr* addr;
        socklen_t len= sizeof(sockaddr_in);
    public:
        explicit Sockaddr(const sockaddr& addr_);
        Sockaddr(const Sockaddr& sockaddr);
        Sockaddr(const char* ip,const char* port);
        Sockaddr& operator=(const Sockaddr& sockaddr);
        ~Sockaddr();
    private:
        sockaddr* getAddr(const char* ip,const char* port);
        const char* getIp(const sockaddr& addr_);
        char* getPort(const sockaddr& addr_);
    };

}


#endif //ETBASE_SOCKADDR_H
