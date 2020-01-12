//
// Created by eight on 1/7/20.
//

#ifndef ETBASE_SOCKET_H
#define ETBASE_SOCKET_H

#include <sys/socket.h>
#include "Socket.h"
#include "Sockaddr.h"

namespace Etbase{
    class Socket {
    public:
        const int domain=AF_INET;
        const int type=SOCK_STREAM;
        const int protocal=0;
        const int fd;
    public:
        Socket();
        Socket(int fd_);
        ~Socket();
        Socket accept(Sockaddr& sock);
        bool bind(Sockaddr& sock);
        bool listen(int num=1024);
        bool connect(const Sockaddr& sock);
        bool write(const char* data);
        int read(char* buff,int size);
        bool setNonBlock();
    };

}


#endif //ETBASE_SOCKET_H
