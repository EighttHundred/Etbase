//
// Created by eight on 1/11/20.
//
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "../Socket.h"

using namespace Etbase;
int main(){
    Sockaddr srvAddr=Sockaddr("127.0.0.1","11111");
    Socket cliSock;
    std::cout<<"fd: "<<cliSock.fd<<std::endl;
    if(!cliSock.connect(srvAddr)) return 123;
    char data[50];
    char buff[100];
    while(std::cin>>data){
        memset(buff,0,sizeof(buff));
        std::cout<<cliSock.write(data)<<std::endl;
        cliSock.read(buff,100);
        std::cout<<buff<<std::endl;
        memset(data,0,sizeof(data));
    }
    close(cliSock.fd);
}