cmake_minimum_required(VERSION 3.15)
project(Etbase)

set(CMAKE_CXX_STANDARD 14)

add_library(Etbase Socket.cpp Socket.h Sockaddr.cpp Sockaddr.h Util.cpp Util.h Test.cpp Test.h)