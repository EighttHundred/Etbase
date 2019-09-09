#include "socket.h"
#include "log.h"
#include <sys/ioctl.h>
#include <linux/if.h>
Etbase::BaseSocket::BaseSocket()
{
    runnable=false;
}
Etbase::BaseSocket::~BaseSocket()
{
    closeFd();
}
int Etbase::BaseSocket::getFd()
{
    if(!runnable){
        LogWriter::writeWarning(-1,"fd get error","no fd attached to this socket","");
        return -1;
    }
    LogWriter::writeDaily(fd,"fd get success","","");
    return fd;
}
int Etbase::BaseSocket::closeFd()
{
    if(!runnable) return;
    if(close(fd)==-1){
        LogWriter::writeWarning(fd,"fd close error","",strerror(errno));
        return -1;
    }
    LogWriter::writeDaily(fd,"fd close success","","");
    return 1;
}

int Etbase::IOSocket::readInfo(char *buff)
{
    if(!runnable){
        LogWriter::writeWarning(-1,"read error","no fd attached to this socket","");
        return -1;
    }
    int len=read(fd,buff,sizeof(buff));
    if(len==-1){
        LogWriter::writeWarning(fd,"read error","",strerror(errno));
        return -1;
    }
    else if(len==0){
        LogWriter::writeDaily(fd,"read EOF","","");
        return 0;
    }
    LogWriter::writeDaily(fd,"read success","","");
    return len;
}

int Etbase::IOSocket::writeInfo(const char *buff)
{
    if(!runnable){
        LogWriter::writeWarning(-1,"write error","no fd attached to this socket","");
        return -1;
    }
    int len=write(fd,buff,sizeof(buff));
    if(len==-1){
        LogWriter::writeWarning(fd,"write error","",strerror(errno));
        return -1;
    }
    LogWriter::writeDaily(fd,"write success","","");
    return len;
}

int Etbase::IOSocket::setNonBlock()
{
    if(!runnable){
        LogWriter::writeWarning(-1,"set non block error","no fd attached to this socket","");
        return -1;
    }
    int flags=fcntl(fd,F_GETFL,0);
    if(flags==-1){
        LogWriter::writeWarning(fd,"set non block error","fd info get error",strerror(errno));
        return -1;
    }
    flags |= O_NONBLOCK;
    if(fcntl(fd,F_SETFL,flags)==-1){
        LogWriter::writeWarning(fd,"set non block error","fd info set error",strerror(errno));
        return -1;
    }
    LogWriter::writeDaily(fd,"set non block success","","");
}

Etbase::AcceptSocket::AcceptSocket(int fd_)
{
    ifreq ifr;
    if(ioctl(fd_,SIOCGIFADDR,&ifr)==-1){
        LogWriter::writeWarning(fd_,"accept socket error","can't get sockaddr by ioctl",strerror(errno));
        return;
    }
    memcpy(&sock,&ifr.ifr_ifru.ifru_addr,sizeof(sock));
    fd=fd_;
    runnable=true;
}

Etbase::ConnectSocket::ConnectSocket(char *host,char *port)
{
    if(host==nullptr){
        LogWriter::writeWarning(-1,"create connect socket error","no host to connect","");
        return;
    }
    int fd_=socket(AF_UNSPEC,SOCK_STREAM,0);
    if(fd<0){
        LogWriter::writeWarning(-1,"create connect socket error","no fd attached to this socket","");
        return;
    }
    bzero(&sock,sizeof(sock));
    sock.sin_family=AF_UNSPEC;
    int port_;
    sscanf(port,"%d",&port_);
    sock.sin_port=htons(port_);
    if(inet_pton(AF_UNSPEC,host,&sock.sin_addr)<0){
        LogWriter::writeWarning(-1,"create connect socket error","format of host is wrong",strerror(errno));
        close(fd);
        return;
    }
    if(connectFd()==-1){
        close(fd);
        return;
    }
    runnable=true;
    LogWriter::writeDaily(fd,"create connect socket success","","");
}

int Etbase::ConnectSocket::connectFd()
{
    if(!runnable){
        LogWriter::writeWarning(-1,"connect error","no fd attached to this socket","");
        return -1;
    }
    if(connect(fd,(sockaddr*)&sock,sizeof(sock))==-1){
        LogWriter::writeWarning(fd,"connect error","",strerror(errno));
        return -1;
    }
    LogWriter::writeDaily(fd,"connect success","","");
    return 1;
}

Etbase::ListenSocket::ListenSocket(char *port)
{
    int on=-1;
    addrinfo hints,*res,*ressave;
    bzero(&hints,sizeof(hints));
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags=AI_PASSIVE;
    if(getaddrinfo(nullptr,port,&hints,&res)!=0){
        LogWriter::writeWarning(-1,"create listen socket error","get addrinfo error",strerror(errno));
        return;
    }
    ressave=res;
    do{
        int fd_=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
        if(fd_<0) continue;
        if(setsockopt(fd_,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))==-1){
            LogWriter::writeWarning(-1,"create listen socket error","set optname error",strerror(errno));
            return;
        }
        if(bind(fd_,(sockaddr*)res->ai_addr,res->ai_addrlen)==0){
            fd=fd_;
            sock=*((sockaddr_in*)res->ai_addr);
            break;
        }
        close(fd_);
    }while((res=res->ai_next)!=nullptr);
    if(res==nullptr){
        LogWriter::writeWarning(-1,"create listen socket error","no adress to bind","");
    }
    freeaddrinfo(ressave);
    if(listenFd()==-1){
        close(fd);
        return;
    }
    runnable=true;
    LogWriter::writeDaily(fd,"create listen socket success","","");
}



int Etbase::ListenSocket::listenFd()
{
    if(!runnable){
        LogWriter::writeWarning(-1,"listen error","no fd attached to this socket","");
        return -1;
    }
    if(listen(fd,LISTENQ)==-1){
        LogWriter::writeWarning(fd,"listen error","",strerror(errno));
        return -1;
    }
    LogWriter::writeDaily(fd,"listen success","","");
    return 1;
}