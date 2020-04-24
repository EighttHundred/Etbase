////
//// Created by eight on 1/7/20.
////
//
//#ifndef ETBASE_SOCKADDR_H
//#define ETBASE_SOCKADDR_H
//
//#include <bits/socket.h>
//#include <netinet/in.h>
//#include <memory>
//namespace Etbase{
//    class Sockaddr {
//    public:
//        const int domain=AF_INET;
//        const int type=SOCK_STREAM;
//        const int protocal=0;
//        const char* port;
//        const char* ip;
//        std::shared_ptr<sockaddr> addr;
//        socklen_t len= sizeof(sockaddr_in);
//    public:
//        explicit Sockaddr(const sockaddr& addr_);
//        Sockaddr(const Sockaddr& sockaddr);
////        Sockaddr(const char* ip,const char* port);
//        explicit Sockaddr(const char* port);
//        Sockaddr& operator=(const Sockaddr& sockaddr);
//        ~Sockaddr();
//    };
//
//}
//
//
//#endif //ETBASE_SOCKADDR_H
