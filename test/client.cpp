//
// Created by eight on 1/11/20.
//
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "../Socket.h"

using namespace Etbase;
using std::cout;
using std::endl;
int main(){
    Socket cliSock;
//    std::cout<<"fd: "<<cliSock.fd<<std::endl;
    if(!cliSock.connect("127.0.0.1","11111")) return 123;
    cout<<"connect success"<<endl;
    char data[50];
    char buff[100];
    while(std::cin>>data){
        int len=strlen(data);
        memset(buff,0,sizeof(buff));
        std::cout<<cliSock.write(data,len)<<std::endl;
        cliSock.read(buff,100);
        std::cout<<buff<<std::endl;
        memset(data,0,sizeof(data));
    }
    cliSock.close();
}