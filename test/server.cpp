//
// Created by eight on 1/11/20.
//
#include <iostream>
#include <cstring>

#include "../include/Reactor.h"
#include "../include/TcpServer.h"
using namespace Etbase;
using std::cout;
using std::endl;
int main(){
    Reactor reactor;
    TcpServer server("11111");
    server.setReadCallback([&server](Socket conn){
        String& buff=server.getBuff(conn.getFd());
        std::cout<<"read data:"<<buff<<" "<<buff.size()<<std::endl;
        cout<<"write "<<conn.write(buff,buff.size())<<endl;
    });
    server.assign(reactor);
    reactor.loop();
}
