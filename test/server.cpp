//
// Created by eight on 1/11/20.
//
#include <iostream>
#include <cstring>

#include "../Reactor.h"
#include "../TcpServer.h"
using namespace Etbase;
using std::cout;
using std::endl;
int main(){
    Reactor reactor;
    reactor.useET(true);
    TcpServer server("11111");
    server.setReadCallback([&server](Socket conn){
        String& buff=server.getBuff(conn.getFd());
        std::cout<<"read data:"<<buff<<std::endl;
        conn.write(buff,buff.size());
    });
    server.assign(reactor);
    reactor.loop();
}
