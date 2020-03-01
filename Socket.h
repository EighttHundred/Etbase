//
// Created by eight on 1/7/20.
//

#ifndef ETBASE_SOCKET_H
#define ETBASE_SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <memory>
#include "Types.h"

namespace Etbase{
    class Socket {
        int domain=AF_INET;
        int type=SOCK_STREAM;
        int protocal=0;
        int fd;
        char buff[2005];
        int wpos=0;
        int rpos=0;
        int buffsize=2000;
        const char* ip;
        const char* port;
        sockaddr_in addr{};
        int socklen=sizeof(sockaddr_in);
        EventType connType=IN;
    public:
        Socket();
        explicit Socket(int fd_,sockaddr_in& addr_);
        int getFd();
        Socket accept();
        bool bind(const char* port_);
        bool listen(int num=1024);
        bool connect(const char* ip_,const char* port_);
        int write(const char* data,size_t len);
        int read();
        bool close();
        EventType getConnType();
        void setConnType(EventType eventType);
        char* getBuffAddr();
        int getRpos();
        int getWpos();
    };

}


#endif //ETBASE_SOCKET_H
