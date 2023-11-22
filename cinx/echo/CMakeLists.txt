cmake_minimum_required(VERSION 3.28)
project(echo)

set(CMAKE_CXX_STANDARD 11)

include_directories(*.h)

add_executable(echo-server server.cpp util.cpp Socket.cpp InetAddress.cpp Epoll.cpp Channel.cpp)
add_executable(echo-client client.cpp util.cpp)
