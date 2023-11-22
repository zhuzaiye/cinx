cmake_minimum_required(VERSION 3.28)
project(cinxcode)

set(CMAKE_CXX_STANDARD 11)

include_directories(*.h)

# socket_epoll
# server_socket from primitive socket
#add_executable(socket-server server_socket.cpp util.cpp)

# server_epoll from socket & epoll
add_executable(echo-server server_epoll.cpp util.cpp)
add_executable(echo-client client.cpp util.cpp)