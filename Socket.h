//
// Created by eight on 1/7/20.
//

#ifndef ETBASE_SOCKET_H
#define ETBASE_SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <memory>

namespace Etbase{
    class Socket {
        int domain=AF_INET;
        int type=SOCK_STREAM;
        int protocal=0;
        int fd;
        const char* ip;
        const char* port;
        sockaddr_in addr{};
        int socklen=sizeof(sockaddr_in);
    public:
        Socket();
        explicit Socket(int fd_,sockaddr_in& addr_);
        int getFd();
        Socket accept();
        bool bind(const char* port_);
        bool listen(int num=1024);
        bool connect(const char* ip_,const char* port_);
        bool write(const char* data,size_t len);
        int read(char* buff,int size);
        bool close();
    };

}


#endif //ETBASE_SOCKET_H
