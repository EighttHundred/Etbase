#ifndef ETBASE_SOCKET_H
#define ETBASE_SOCKET_H

#include <error.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <string.h>

#define LISTENQ 1024

namespace Etbase
{
    class BaseSocket
    {
    public:
        BaseSocket();
        ~BaseSocket();
        int getFd();
    protected:
        int closeFd();
        int fd;
        bool runnable;
        sockaddr_in sock;
    };
    
    class IOSocket:public BaseSocket
    {
    public:
        int readInfo(char *buff);
        int writeInfo(const char *buff);
        int setNonBlock();
    };

    class AcceptSocket:public IOSocket
    {
        AcceptSocket(int fd_);
    };

    class ConnectSocket:public IOSocket
    {   
    public:
        ConnectSocket(char *host,char *port);
    private:
        int connectFd();
    };

    class ListenSocket:public BaseSocket
    {
    public:
        ListenSocket(char *port);
        AcceptSocket accept();
    private:
        int listenFd();
    };
}

#endif //ETBASE_SOCKET_H
