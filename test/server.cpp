//
// Created by eight on 1/11/20.
//
#include <iostream>
#include <cstring>

#include "../include/Reactor.h"
#include "../include/TcpConnector.h"
using namespace Etbase;
using namespace std;
int main(){
    Reactor reactor;
    TcpConnector server(reactor);
    server.initServer("11111");
    server.setReadCallback([&server](Socket conn){
        String buff=server.getBuff(conn.getFd());
        cout<<"read data:"<<buff<<endl;
//        int ret=conn.write(buff);
//        if(ret<0){
//            server.
//        }
//        cout<<"write "<<buff.getWriteSize()<<endl;
    });
    server.start();
}
