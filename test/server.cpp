//
// Created by eight on 1/11/20.
//
#include <iostream>
#include <cstring>

#include "../Reactor.h"
#include "../Socket.h"
using namespace Etbase;

Reactor reactor;
Socket srvsock;
Sockaddr sockaddr("11111");

int listenfd;
char buff[100];
using std::cout;
using std::endl;
void connFunc(int fd){
    Socket cliSock(fd);
    while(true){
        int ret=cliSock.read(buff,100);
        if(ret==0){
            std::cout<<"conn "<<fd<<" close \n";
            break;
        }else if(ret<0){
            if(errno==EAGAIN){
                std::cout<<"read later\n";
                reactor.acceptor.resetOneShot(fd);
                break;
            }else{
                std::cout<<"error\n";
                exit(-1);
            }

        }else{
            std::cout<<"read data: "<<buff<<"\n";
            cliSock.write(buff);
        }
    }
    cout<<"conn "<<fd<<" closed\n";
}

void serverFunc(int fd){
    Event event;
    Socket cliSock=srvsock.accept(sockaddr);
    if(cliSock.fd==-1){
        cout<<"accept error"<<endl;
        cout<<"errno: "<<errno<<endl;
        return;
    }else{
        cout<<"accept success\n";
        cout<<"fd:"<<cliSock.fd<<endl;
    }
    event.fd=cliSock.fd;
    event.handler=connFunc;
    event.type=SERVER;
    reactor.regist(event);
}

int main(){

    listenfd=srvsock.fd;

    srvsock.bind(sockaddr);
    std::cout<<"listen:  "<<srvsock.listen()<<std::endl;

    Event event;
    event.fd=srvsock.fd;
    event.handler=serverFunc;
    reactor.regist(event);
//    std::cout<<"quque"<<reactor.pool.evqueue->push(event)<<std::endl;

//    reactor.active(event.fd);
    reactor.loop();

}





//int main(){
//    Sockaddr cliAddr=Sockaddr("");
//    Sockaddr srvAddr("11111");
//    Socket srvSock;
//    std::cout<<srvSock.bind(srvAddr)<<std::endl;
//    std::cout<<srvSock.listen()<<std::endl;
//    std::cout<<srvSock.fd<<std::endl;
//    char buff[100];
//    memset(buff,0,sizeof(buff));
//    while(true){
//        Socket cliSock=srvSock.accept(cliAddr);
//        std::cout<<cliSock.fd<<" "<<cliAddr.ip<<" "<<cliAddr.port<<" ."<<std::endl;
//        while(cliSock.read(buff,100)>0){
//            std::cout<<buff<<std::endl;
//            cliSock.write(buff);
//            memset(buff,0,sizeof(buff));
//        }
//    }
//}