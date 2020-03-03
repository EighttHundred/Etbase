cmake_minimum_required(VERSION 3.15)
project(Etbase)

set(CMAKE_CXX_STANDARD 14)

add_library(Etbase Etbase/Socket.cpp include/Socket.h Etbase/Util.cpp include/Util.h include/Acceptor.h include/Etbase.h Etbase/Reactor.cpp include/Reactor.h Etbase/Epoll.cpp include/Types.h include/Epoll.h Etbase/Mutex.cpp include/Mutex.h Etbase/EventMap.cpp include/EventMap.h Etbase/Event.cpp include/Event.h Etbase/EventQueue.cpp include/EventQueue.h Etbase/ThreadPool.cpp include/ThreadPool.h Etbase/String.cpp include/String.h Etbase/TcpServer.cpp include/TcpServer.h)
#link_libraries(Etbase)
add_executable(Test test/test.cpp)
add_executable(Client test/client.cpp)
add_executable(Server test/server.cpp )
target_link_libraries(Test Etbase pthread)
target_link_libraries(Client Etbase pthread)
target_link_libraries(Server Etbase pthread)