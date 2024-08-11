cmake_minimum_required(VERSION 3.23)
project(echo)

set(CMAKE_CXX_STANDARD 11)

include_directories(*.h)

add_executable(echo-server server.cpp src/util.cpp src/Socket.cpp src/InetAddress.cpp src/Epoll.cpp src/Channel.cpp src/Eventloop.cpp src/Server.cpp)
add_executable(echo-client client.cpp src/util.cpp)
