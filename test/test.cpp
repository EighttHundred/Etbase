//
// Created by eight on 1/11/20.
//
#include <iostream>

#include "../Reactor.h"
#include "../Socket.h"
using namespace Etbase;

void serverFunc(int fd){
    std::cout<<"hello";
}

int main(){
    Socket socket;
    Sockaddr sockaddr("2222");
    socket.bind(sockaddr);
    std::cout<<"listen:  "<<socket.listen()<<std::endl;
    Reactor reactor;
    Event event;
    event.fd=socket.fd;
    event.handler=serverFunc;
    reactor.regist(event);
    reactor.active(event.fd);
    reactor.run();
}