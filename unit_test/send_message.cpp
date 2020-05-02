#include <iostream>
#include "../include/Reactor.h"
#include "../include/TcpConnector.h"
#include "tools.h"
using namespace Etbase;
using namespace std;
int main(){
    Reactor reactor;
    TcpConnector client(reactor);
    Buffer data="hello";
    client.initSender("127.0.0.1","11111",2);
    client.setSendData(data);
    client.start();
    return 0;
}