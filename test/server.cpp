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
    server.setConnHandler([&server](EventPtr conn,BufferPtr buffer){
        cout<<"read data:"<<buffer<<endl;
    });
    server.start();
}
