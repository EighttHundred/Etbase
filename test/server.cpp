//
// Created by eight on 1/11/20.
//
#include <iostream>
#include <cstring>

#include "../Reactor.h"
#include "../TcpServer.h"
using namespace Etbase;

int listenfd;
char buff[100];
using std::cout;
using std::endl;

static void processRead(Socket conn){
    std::cout<<"read data:"<<conn.getBuffAddr()<<std::endl;
    conn.write(conn.getBuffAddr(),conn.getRpos());
}
int main(){
    Reactor reactor;
    reactor.useET(true);
    TcpServer server("11111");
    server.setRead(processRead);
    server.assign(reactor);
    reactor.loop();
}
