#ifndef ETBASE_SOCKET_H
#define ETBASE_SOCKET_H

#include <error.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include "../base/log.h"

#define LISTENQ 1024

namespace Etbase
{
    class Socket {
    public:
        Socket():fd(-1)
        {

        }
        ~Socket()
        {
            closeFd();
        }
        int getFd()
        {
            return fd;
        }
        void createByPort(char* port)
        {
            addrinfo hints;
            addrinfo *result;
            memset(&hints,0,sizeof(addrinfo));
            hints.ai_family=AF_UNSPEC;
            hints.ai_socktype=SOCK_STREAM;
            hints.ai_flags=AI_PASSIVE;
            if(getaddrinfo(NULL,port,&hints,&result)!=0){
                char msg[ERRORLEN];
                sprintf(msg,"can't get addrinfo,error is: %s.",strerror(errno));
                LogWriter::writeError(msg);
                return;
            }
            int tfd=-1;
            for(auto rp=result;rp!=NULL;rp=rp->ai_next)
            {
                tfd=socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
                if(tfd!=-1){
                    break;
                }
            }
            if(tfd!=-1){
                fd=tfd;
            }
        }
        void createByIpPort(char* ip,int port)
        {
            sock.sin_family=AF_INET;
            sock.sin_port=htons(port);
            if(inet_pton(AF_INET,ip,&sock.sin_addr)<=0){
                char msg[ERRORLEN];
                sprintf(msg,"ip %s error,error is: %s.",ip,strerror(errno));
                LogWriter::writeError(msg);
                return;
            }
        }
        void setNonBlock()
        {
            int flags;
            flags=fcntl(fd,F_GETFL,0);
            if(flags==-1){
                return;
            }
            flags |= O_NONBLOCK;
            if(fcntl(fd,F_SETFL,flags)==-1){
                return;
            }
            LogWriter::writeDaily("set fd non block success");
        }
        void Bind(char *port)
        {
            if(bind(fd,(sockaddr*)&sock,socklen)==-1){
                char msg[ERRORLEN];
                sprintf(msg,"socket %d bind failed,error is: %s.",fd,strerror(errno));
                LogWriter::writeError(msg);
            }
        }
        void Connect()
        {
            if(connect(fd,(sockaddr*)&sock,socklen)==-1){
                char msg[ERRORLEN];
                sprintf(msg,"socket %d connect failed,error is: %s.",fd,strerror(errno));
                LogWriter::writeError(msg);
            }
        }
        void Listen()
        {
            if(listen(fd,LISTENQ)==-1){
                char msg[ERRORLEN];
                sprintf(msg,"socket %d listen failed,error is: %s.",fd,strerror(errno));
                LogWriter::writeError(msg);
            }
        }
        void Write(char* buff)
        {
            write(fd,buff,sizeof(buff));
        }
        int Read(char* buff)
        {
            int len=read(fd,buff,sizeof(buff));
            return len;
        }
    private:
        int getSocket()
        {
            int sockfd=socket(AF_INET,SOCK_STREAM,0);
            if(sockfd==-1){
                char msg[ERRORLEN];
                sprintf(msg,"socket %d close failed,error is: %s.",fd,strerror(errno));
                LogWriter::writeError(msg);
            }
            return sockfd;
        }
        void closeFd()
        {
            if(fd==-1){
                return;
            }
            if(close(fd)==-1){
                char msg[ERRORLEN];
                sprintf(msg,"sock accquire failed,error is: %s.",strerror(errno));
                LogWriter::writeError(msg);
            }
        }
        int fd;
        sockaddr_in sock;
        socklen_t socklen;
    };
}



#endif //ETBASE_SOCKET_H
