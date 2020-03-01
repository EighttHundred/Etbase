//
// Created by eight on 1/11/20.
//
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "../Socket.h"
//#include <string>
using namespace Etbase;
using std::cout;
using std::endl;
using std::cin;
int main(){
    Socket cliSock;
    if(!cliSock.connect("127.0.0.1","11111")) return 123;
    cout<<"connect success"<<endl;
    String data;
    String buff;
    while(cin>>data){
        cliSock.write(data,data.size());
        cliSock.read(buff);
        std::cout<<buff<<std::endl;
//        std::cout<<"echo:\n";
//        cout<<buff.begin();
//        putchar('\n');
    }
    cliSock.close();
}