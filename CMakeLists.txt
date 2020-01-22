cmake_minimum_required(VERSION 3.15)
project(Etbase)

set(CMAKE_CXX_STANDARD 14)

add_library(Etbase Socket.cpp Socket.h Sockaddr.cpp Sockaddr.h Util.cpp Util.h Acceptor.h Etbase.h Reactor.cpp Reactor.h Epoll.cpp Types.h Epoll.h useless/Dispatcher.h Mutex.cpp Mutex.h EventMap.cpp EventMap.h Event.cpp Event.h EventQueue.cpp EventQueue.h useless/MultithreadDispatcher.cpp useless/MultithreadDispatcher.h ThreadPool.cpp ThreadPool.h)
#link_libraries(Etbase)
add_executable(Test test/test.cpp)
add_executable(Client test/client.cpp)
add_executable(Server test/server.cpp )
target_link_libraries(Test Etbase pthread)
target_link_libraries(Client Etbase pthread)
target_link_libraries(Server Etbase pthread)