//
// Created by eight on 1/11/20.
//
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "../include/Socket.h"
#include "../include/Reactor.h"
//#include <string>
#include "../include/Socket.h"
#include "../include/TcpClient.h"
#include "../include/TcpConnector.h"
using namespace Etbase;
using std::cout;
using std::endl;
using std::cin;
int main(){
//    int ret=0;
//    Socket socket;
//    ret=socket.connect("127.0.0.1", "11111");
//    if(ret==1){
//        socket.setNonBlock(true);
//        String data;
//        while(true){
//            cin>>data;
//            socket.write(data);
//            socket.read(data);
//            cout<<"receive: "<<data<<endl;
//        }
//    }
    TcpClient tcpClient("127.0.0.1","11111");
    String data;
    while(true){
        cin>>data;
        tcpClient.sendData(data);
    }
}