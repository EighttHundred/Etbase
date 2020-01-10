//
// Created by eight on 1/7/20.
//

#ifndef NET_SOCKET_H
#define NET_SOCKET_H

#include <sys/socket.h>
#include "Socket.h"
#include "Sockaddr.h"

namespace ehd{
    class Socket {
    public:
        //order is important
        const Sockaddr*const sock;
        const int fd;
    public:
        Socket(const char* ip=nullptr,const char* port=nullptr);
        Socket(int fd_,const Sockaddr *sock_);
        ~Socket();
        Socket accept();
        bool bind();
        bool listen(int num=1024);
        bool connect(const Sockaddr& sock_);
    };

}


#endif //NET_SOCKET_H
