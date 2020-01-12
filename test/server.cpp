//
// Created by eight on 1/11/20.
//
#include <iostream>
#include "../Socket.h"

using namespace Etbase;

int main(){
    Sockaddr cliAddr=Sockaddr("");
    Sockaddr srvAddr("11111");
    Socket srvSock;
    std::cout<<srvSock.bind(srvAddr)<<std::endl;
    std::cout<<srvSock.listen()<<std::endl;
    char buff[100];
    while(true){
        Socket cliSock=srvSock.accept(cliAddr);
        std::cout<<cliSock.fd<<" "<<cliAddr.ip<<" "<<cliAddr.port<<" ."<<std::endl;
        while(cliSock.read(buff,100)>0){
            std::cout<<buff<<std::endl;
        }
    }
}