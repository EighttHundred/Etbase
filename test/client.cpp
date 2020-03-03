//
// Created by eight on 1/11/20.
//
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "../include/Socket.h"
#include "../include/Reactor.h"
//#include <string>
using namespace Etbase;
using std::cout;
using std::endl;
using std::cin;
int main(){
    Reactor reactor;
    Socket cliSock;
    if(cliSock.connect("127.0.0.1","11111")){
        cout<<"connect success"<<endl;
        String data;
        String buff;
        cliSock.setNonBlock();
        while(cin>>data){
            cliSock.write(data,data.size());
            cout<<"read: "<<cliSock.read(buff)<<endl;
            std::cout<<buff<<std::endl;
//        std::cout<<"echo:\n";
//        cout<<buff.begin();
//        putchar('\n');
        }
        cliSock.close();
    }else{
        cout<<"fail"<<endl;
    }
}