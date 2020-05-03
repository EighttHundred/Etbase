// //
// // Created by eighthundred on 2020/4/24.
// //

// #include "../include/HttpServer.h"
// using namespace Etbase;
// //
// // Created by cheng on 2019/4/30.
// //

// #include <thread>
// #include <algorithm>
// #include <sys/stat.h>
// #include <sstream>
// #include <unistd.h>
// #include <wait.h>
// #include "Server.h"
// #include "util.h"
// #include "Data.h"
// #include "ErrorPage.h"

// #define ST_NEED_TO_EXECUTE_CGI(st) \
//     (((st).st_mode & S_IXUSR) || \
//     ((st).st_mode & S_IXGRP) || \
//     ((st).st_mode & S_IXOTH))

// #define ST_IS_DIR(st) \
//     (st.st_mode & S_IFMT) == S_IFDIR

// #define PIPE_STEP 0x100

// Server::Server(const string &serverRoot, const string &serverFiles, const string &cgiBin, const Mime &mime) :
//         serverFiles(serverFiles),
//         serverRoot(serverRoot),
//         cgiBin(cgiBin),
//         mime(mime) {
//     while (!this->serverFiles.empty() && this->serverFiles.back() == '/') {
//         this->serverFiles.pop_back();
//     }
//     while (!this->serverRoot.empty() && this->serverRoot.back() == '/') {
//         this->serverRoot.pop_back();
//     }
//     while (!this->cgiBin.empty() && this->cgiBin.back() == '/') {
//         this->cgiBin.pop_back();
//     }
// }

// Server::~Server() {}

// bool Server::init(int port) {
//     PRINTFLN("started to initialize server, port: '%d'", port);

//     if (!listenerFD.init(port)) {
//         PRINTFLN_ERROR("failed to initialize server, port: '%d'", port);
//         return false;
//     }

//     PRINTFLN("finished initializing server, port: '%d'", port);
//     return true;
// }

// void Server::handleHTTPRequest() const {
//     SocketFD *client = listenerFD.accept();
//     if (!client) {
//         PRINTFLN_ERROR("error while invoking accept procedure");
//         return;
//     }
//     PRINTFLN("got new client from accept, peer: '%s'", client->getIpString().c_str());

//     PRINTFLN("creating new thread to handle this request");
//     thread t(Task(), this, client);
//     t.detach();
//     PRINTFLN("thread detached");
// }

// void Server::handleHTTPRequest(const SocketFD *client) const {
//     string firstLineStr = client->getLine().toString();

//     string method, url, version;
//     handleFistLine(firstLineStr, method, url, version);

//     PRINTFLN("handling HTTP request, method: '%s'", method.c_str());
//     if (method == "POST") {
//         handlePost(*client, url);
//     } else if (method == "GET") {
//         handleGet(*client, url);
//     } else {
//         PRINTFLN("unimplemented HTTP method, responding error page");
//         send501(*client);
//     }

//     delete client;
//     PRINTFLN("request & response finished");
// }

// void Server::handleGet(const SocketFD &client, const string &url) const {
//     bool cgiFlag = false;
//     size_t questionMarkIndex = url.find('?');

//     string queryString;
//     if (questionMarkIndex != string::npos) {
//         queryString = url.substr(questionMarkIndex + 1);
//         PRINTFLN("extracted query string: '%s'", queryString.c_str());
//     }

//     string path = url.substr(0, questionMarkIndex);

//     string realPath;
//     if (path.substr(0, 5) == "/cgi/") {
//         realPath = cgiBin + path.substr(4);
//         cgiFlag = true;
//     } else {
//         realPath = serverFiles + path;
//     }

//     struct stat st;
//     if (stat(realPath.c_str(), &st) == -1) {
//         perror("stat");
//         PRINTFLN("requested target not exists, path: '%s'", realPath.c_str());
//         discardHeaders(client);
//         send404(client);
//     } else {
//         if (cgiFlag) {
//             if (ST_IS_DIR(st)) {
//                 PRINTFLN("CGI requested target cannot be a directory, path: '%s'", realPath.c_str());
//                 discardHeaders(client);
//                 send404(client);
//             }
//             else {
//                 executeCGI(client, realPath, "GET", queryString);
//             }
//         } else {
//             if (ST_IS_DIR(st)) {
//                 realPath.append("/index.html");
//                 if (stat(realPath.c_str(), &st) == -1) {
//                     PRINTFLN("requested target not exists, path: '%s'", realPath.c_str());
//                     discardHeaders(client);
//                     send404(client);
//                 } else if (ST_IS_DIR(st)) {
//                     PRINTFLN("requested target is a directory after URL extension, path: '%s'", realPath.c_str());
//                     discardHeaders(client);
//                     send404(client);
//                 } else {
//                     serveFile(client, realPath);
//                 }
//             } else {
//                 serveFile(client, realPath);
//             }
//         }
//     }
// }

// void Server::handlePost(const SocketFD &client, const string &url) const {
//     bool cgiFlag = false;
//     const string& path = url;
//     string realPath;
//     if (path.substr(0, 5) == "/cgi/") {
//         realPath = cgiBin + path.substr(4);
//         cgiFlag = true;
//     } else {
//         realPath = serverFiles + path;
//     }

//     struct stat st;
//     if (stat(realPath.c_str(), &st) == -1) {
//         perror("stat");
//         PRINTFLN("requested target not exists, path: '%s'", realPath.c_str());
//         discardHeaders(client);
//         send404(client);
//     } else {
//         if (cgiFlag) {
//             if (ST_IS_DIR(st)) {
//                 PRINTFLN("CGI requested target cannot be a directory, path: '%s'", realPath.c_str());
//                 discardHeaders(client);
//                 send404(client);
//             }
//             else {
//                 executeCGI(client, realPath, "POST", "");
//             }
//         } else {
//             if (ST_IS_DIR(st)) {
//                 realPath.append("/index.html");
//                 if (stat(realPath.c_str(), &st) == -1) {
//                     PRINTFLN("requested target not exists, path: '%s'", realPath.c_str());
//                     discardHeaders(client);
//                     send404(client);
//                 } else if (ST_IS_DIR(st)) {
//                     PRINTFLN("requested target is a directory after URL extension, path: '%s'", realPath.c_str());
//                     discardHeaders(client);
//                     send404(client);
//                 } else {
//                     serveFile(client, realPath);
//                 }
//             } else {
//                 serveFile(client, realPath);
//             }
//         }
//     }
// }

// bool Server::sendResponseLine(const SocketFD &client) const {
//     return client.send("HTTP/1.0 200 OK" CRLF);
// }

// bool Server::sendResponseHeaders(const SocketFD &client, const string &contentType) const {
//     PRINTFLN("sending response headers, Content-Type: '%s'", contentType.c_str());

//     stringstream ss;

//     ss << "Content-Type: " << contentType << CRLF;

//     return client.send(ss.str());
// }

// bool Server::sendEmptyLine(const SocketFD &client) const {
//     return client.send(CRLF);
// }

// bool Server::sendResponse(const SocketFD &client, const string &contentType, const Data &body) const {
//     return sendResponseLine(client) &&
//         sendResponseHeaders(client, contentType) &&
//         sendEmptyLine(client) &&
//         client.send(body);
// }

// bool Server::send400(const SocketFD &client) const {
//     PRINTFLN("bad request, responding error page");

//     stringstream ss;

//     ss << "HTTP/1.0 400 BAD REQUEST" << CRLF;
//     ss << "Content-Type: text/html" << CRLF;
//     ss << CRLF;
//     ss << ErrorPage::get(400);

//     return client.send(ss.str());
// }

// bool Server::send404(const SocketFD &client) const {
//     PRINTFLN("requested resource not found, responding error page");
//     stringstream ss;

//     ss << "HTTP/1.0 404 NOT FOUND" << CRLF;
//     ss << "Content-Type: text/html" << CRLF;
//     ss << CRLF;
//     ss << ErrorPage::get(404);

//     return client.send(ss.str());
// }

// bool Server::send500(const SocketFD &client) const {
//     PRINTFLN("internal server error occurred, responding error page");
//     stringstream ss;

//     ss << "HTTP/1.0 500 INTERNAL SERVER ERROR" << CRLF;
//     ss << "Content-Type: text/html" << CRLF;
//     ss << CRLF;
//     ss << ErrorPage::get(500);

//     return client.send(ss.str());
// }

// bool Server::send501(const SocketFD &client) const {
//     PRINTFLN("unimplemented HTTP method, responding error page");
//     stringstream ss;

//     ss << "HTTP/1.0 501 NOT IMPLEMENTED" << CRLF;
//     ss << "Content-Type: text/html" << CRLF;
//     ss << CRLF;
//     ss << ErrorPage::get(501);

//     return client.send(ss.str());
// }

// void Server::serveFile(const SocketFD &client, const string &path) const {
//     PRINTFLN("locating requested file, path: '%s'", path.c_str());

//     Data data;
//     if (!data.initFromFile(path)) {
//         PRINTFLN_ERROR("failed to load data from file, path: '%s'", path.c_str());
//         send404(client);
//         return;
//     }

//     discardHeaders(client);

//     string contentType = mime.getType(path);

//     PRINTFLN("finished loading file data, sending it");
//     sendResponse(client, contentType, data);
// }

// void Server::handleFistLine(const string &firstLine, string &method, string &url, string &version) const {
//     stringstream ss;
//     ss << firstLine << endl;
//     ss >> method >> url >> version;

//     PRINTFLN("first line of headers got parsed, method: '%s', URL: '%s', version: '%s'", method.c_str(), url.c_str(), version.c_str());
// }

// void
// Server::executeCGI(const SocketFD &client, const string &path, const string &method, const string &queryString) const {
//     int contentLength = -1;
//     PRINTFLN("started to execute CGI, method: '%s', path: '%s', query string: '%s'", method.c_str(), path.c_str(), queryString.c_str());
//     if (method == "GET") {
//         discardHeaders(client);
//     } else if (method == "POST") {
//         while (true) {
//             Data data = client.getLine();
//             string dataStr = data.toString();
//             if (data.getLength() == 0 || dataStr == CRLF) {
//                 break;
//             } else {
//                 string attrPrefix = dataStr.substr(0, 15);
//                 for_each(attrPrefix.begin(), attrPrefix.end(), ::toupper);
//                 if (attrPrefix == "CONTENT-LENGTH:") {
//                     contentLength = ::stoi(dataStr.substr(16));
//                 }
//             }
//         }
//         if (contentLength == -1) {
//             PRINTFLN("cannot execute CGI, failed to parse Content-Length in request headers");
//             send400(client);
//             return;
//         }
//     } else {
//         PRINTFLN("improper method for executing CGI");
//     }

//     int cgiOutput[2], cgiInput[2], pid;
//     if (pipe(cgiOutput) < 0 || pipe(cgiInput) < 0) {
//         PRINTFLN_ERROR("unable to establish pipe");
//         send500(client);
//         return;
//     }

//     if ((pid = fork()) < 0) {
//         PRINTFLN_ERROR("unable to fork");
//         send500(client);
//         return;
//     }

//     sendResponseLine(client);

//     if (pid == 0) {
//         dup2(cgiOutput[1], STDOUT);
//         dup2(cgiInput[0], STDIN);
//         close(cgiOutput[0]);
//         close(cgiInput[1]);

//         setenv("REQUEST_METHOD", method.c_str(), 1);
//         if (method == "GET") {
//             setenv("QUERY_STRING", queryString.c_str(), 1);
//         } else {
//             setenv("CONTENT_LENGTH", ::to_string(contentLength).c_str(), 1);
//         }
//         execl(path.c_str(), nullptr);
//         exit(0);
//     } else {
//         close(cgiOutput[1]);
//         close(cgiInput[0]);
//         if (method == "POST") {
//             PRINTFLN("receiving data from client and writing it to CGI input");
//             for (int i = 0; i < contentLength; i += PIPE_STEP) {
//                 Data data = client.receive(PIPE_STEP);
//                 write(cgiInput[1], data.getBuffer(), data.getLength());
//             }
//         }

//         PRINTFLN("reading data from CGI output and sending it to client");
//         while (true) {
//             char *buffer = new char[PIPE_STEP];
//             ssize_t n = read(cgiOutput[0], buffer, PIPE_STEP);
//             if (n <= 0) {
//                 break;
//             }
//             Data data;
//             data.moveFromBuffer(buffer, n);
//             client.send(data);
//         }

//         close(cgiOutput[0]);
//         close(cgiInput[1]);

//         int status;
//         PRINTFLN("waiting child process to exit");
//         waitpid(pid, &status, 0);
//         PRINTFLN("child process exited");
//     }
// }

// void Server::discardHeaders(const SocketFD &client) const {
//     PRINTFLN("discarding remaining request headers");

//     while (true) {
//         Data data = client.getLine();
//         if (data.getLength() == 0 || data.toString() == CRLF) {
//             break;
//         }
//     }
// }

// void Server::discardAll(const SocketFD &client) const {
//     PRINTFLN("discarding all remaining request content");

//     while (client.getLine().getLength() != 0);
// }