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

int listenfd;
char buff[100];
using std::cout;
using std::endl;
void connFunc(Socket connsock){

    while(true){
        int ret,len=0;
        while((ret=connsock.read(buff+len,100-len))>0)
            len+=ret;
        if(len>0){
            cout<<"read data: ";
            for(int i=0;i<len;++i)
                putchar(buff[i]);
            putchar('\n');
            connsock.write(buff,len);
        }
        if(ret==0){
            cout<<"conn "<<connsock.getFd()<<" closed\n";
            break;
        }else if(ret<0){
            if(errno==EAGAIN){
                std::cout<<"read later\n";
                reactor.acceptor.resetOneShot(connsock.getFd());
                break;
            }else{
                std::cout<<"error..close\n";
                exit(-1);
            }
        }
    }
}

void serverFunc(Socket socket){
    Event event;
    Socket cliSock=srvsock.accept();
    if(cliSock.getFd()==-1){
        cout<<"accept error"<<endl;
        cout<<"errno: "<<errno<<endl;
        return;
    }else{
        cout<<"accept success\n";
        cout<<"fd:"<<cliSock.getFd()<<endl;
    }
    event.sock=cliSock;
    event.fd=cliSock.getFd();
    event.handler=connFunc;
    event.type=SERVER;
    reactor.regist(event);
}

int main(){

    listenfd=srvsock.getFd();

    srvsock.bind("11111");
    std::cout<<"listen:  "<<srvsock.listen()<<std::endl;

    Event event;
    event.fd=srvsock.getFd();
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