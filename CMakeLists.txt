cmake_minimum_required(VERSION 3.15)
project(Etbase)

set(CMAKE_CXX_STANDARD 14)

add_library(Etbase src/Socket.cpp include/Socket.h src/Util.cpp include/Util.h
        include/Acceptor.h include/Etbase.h src/Reactor.cpp include/Reactor.h src/Epoll.cpp
        include/Types.h include/Epoll.h src/Mutex.cpp include/Mutex.h src/EventMap.cpp
        include/EventMap.h src/Event.cpp include/Event.h src/EventQueue.cpp include/EventQueue.h
        src/ThreadPool.cpp include/ThreadPool.h src/String.cpp include/String.h
        src/TcpServer.cpp include/TcpServer.h src/TcpClient.cpp include/TcpClient.h src/HttpClient.cpp include/HttpClient.h src/Timer.cpp include/Timer.h src/TcpConnector.cpp include/TcpConnector.h)
#link_libraries(Etbase)
add_executable(Test test/test.cpp)
add_executable(Client test/client.cpp)
add_executable(Server test/server.cpp )
target_link_libraries(Test Etbase pthread)
target_link_libraries(Client Etbase pthread)
target_link_libraries(Server Etbase pthread)