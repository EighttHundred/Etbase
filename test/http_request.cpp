
#include "../include/Reactor.h"
#include "../include/TcpConnector.h"
using namespace Etbase;
using namespace std;
int main(){
    Reactor reactor;
    TcpConnector requestor(reactor);
    String data="hello";
    requestor.initSender("baidu.com","80",2);
    requestor.setSendData(data);
    
    // requestor.initServer("")
    requestor.start();
}