//
// Created by eight on 1/11/20.
//
#include <iostream>
#include <cstring>

#include "../Reactor.h"
#include "../TcpServer.h"
using namespace Etbase;

int listenfd;
using std::cout;
using std::endl;

static void processRead(Socket conn){
    String& buff=TcpServer::getBuff(conn.getFd());
    std::cout<<"read data:"<<buff<<std::endl;
    conn.write(buff,buff.size());
}
int main(){
    Reactor reactor;
    reactor.useET(true);
    TcpServer server("11111");
    server.setRead(processRead);
    server.assign(reactor);
    reactor.loop();
}
