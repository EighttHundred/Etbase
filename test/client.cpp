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
    char* buff=cliSock.getBuffAddr();
    while(std::cin>>data){
        int len=strlen(data);
        std::cout<<cliSock.write(data,len)<<std::endl;
        cliSock.read();
//        std::cout<<buff<<std::endl;
        int rlen=cliSock.getRpos();
        std::cout<<"echo:\n";
        for(int i=0;i<rlen;++i){
            putchar(buff[i]);
        }
        putchar('\n');
    }
    cliSock.close();
}