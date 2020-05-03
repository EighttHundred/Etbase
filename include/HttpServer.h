// //
// // Created by eighthundred on 2020/4/24.
// //

// #ifndef ETBASE_HTTPSERVER_H
// #define ETBASE_HTTPSERVER_H

// namespace Etbase{

//     class HttpParser{
        
//     };
//     class HttpServer {

//     };
// }



// #endif //ETBASE_HTTPSERVER_H
// //
// // Created by cheng on 2019/4/30.
// //

// #ifndef WEBMIN_SERVER_H
// #define WEBMIN_SERVER_H


// #include <string>
// #include "SocketFD.h"
// #include "Data.h"
// #include "Mime.h"

// using namespace std;

// class Server {
// public:
//     Server(const string &serverRoot, const string &serverFiles, const string &cgiBin, const Mime &mime);
//     ~Server();
//     bool init(int port);
//     void handleHTTPRequest() const;

// private:
//     struct Task {
//         void operator()(const Server *server, const SocketFD *client) {
//             server->handleHTTPRequest(client);
//         }
//     };
//     void handleHTTPRequest(const SocketFD *client) const;
//     bool send400(const SocketFD &client) const;
//     bool send404(const SocketFD &client) const;
//     bool send500(const SocketFD &client) const;
//     bool send501(const SocketFD &client) const;
//     bool sendResponseLine(const SocketFD &client) const;
//     bool sendResponseHeaders(const SocketFD &client, const string &contentType) const;
//     bool sendEmptyLine(const SocketFD &client) const;
//     bool sendResponse(const SocketFD &client, const string &contentType, const Data &body) const;
//     void serveFile(const SocketFD &client, const string &path) const;
//     void handleFistLine(const string &firstLine, string &method, string &url, string &version) const;
//     void handleGet(const SocketFD &client, const string &url) const;
//     void handlePost(const SocketFD &client, const string &url) const;
//     void executeCGI(const SocketFD &client, const string &path, const string &method, const string &queryString) const;
//     void discardHeaders(const SocketFD &client) const;
//     void discardAll(const SocketFD &client) const;

//     SocketFD listenerFD;
//     string serverFiles;
//     string serverRoot;
//     string cgiBin;
//     const Mime &mime;
// };


// #endif //WEBMIN_SERVER_H