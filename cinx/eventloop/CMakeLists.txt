cmake_minimum_required(VERSION 3.28)
project(eventloop)

set(CMAKE_CXX_STANDARD 11)

# 获取 src 目录下的所有源文件
file(GLOB SOURCE_FILES "src/*.cpp")

# 为 server.cpp 指定源文件
set(SERVER_SOURCE_FILES server.cpp src/util.cpp src/Socket.cpp src/InetAddr.cpp src/Epoll.cpp src/Channel.cpp src/EventLoop.cpp src/Server.cpp)

# 为 client.cpp 指定源文件
set(CLIENT_SOURCE_FILES client.cpp src/util.cpp)

# 添加 server 可执行文件并列出所有源文件
add_executable(server ${SOURCE_FILES} ${SERVER_SOURCE_FILES})

# 添加 client 可执行文件并列出所有源文件
add_executable(client ${SOURCE_FILES} ${CLIENT_SOURCE_FILES})
