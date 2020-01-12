//
// Created by eight on 1/11/20.
//
#include <iostream>
#include "../Socket.h"

using namespace Etbase;
int main(){
    Sockaddr srvAddr=Sockaddr("127.0.0.1","11111");
    Socket cliSock;
    std::cout<<cliSock.connect(srvAddr)<<std::endl;
    char data[50];
    while(std::cin>>data){
        std::cout<<cliSock.write(data)<<std::endl;

    }
}