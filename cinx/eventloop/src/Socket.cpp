// Copyright (c) 2023/11/21 by hzzhu92
// Socket.cpp

#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include "Socket.h"
#include "InetAddr.h"
#include "util.h"

Socket::Socket() : fd(-1) {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    err_if(fd == -1, "socket create error");
}

Socket::Socket(int _fd) : fd(_fd) {
    err_if(fd == -1, "socket create error");
}

Socket::~Socket() {
    if (fd != -1) {
        close(fd);  // 关闭socket文件描述符
        fd = -1;    // socket fd回到初始状态
    }
}

int Socket::get_fd() {
    return fd;
}

void Socket::set_nonblocking() {
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

/* 给fd绑定intel 地址 */
void Socket::bind(InetAddr *inet_addr) {
    int bind_res = ::bind(fd, (sockaddr *) &inet_addr->addr, inet_addr->addr_len);
    err_if(bind_res == -1, "socket bind addr error");
}

/* 启动fd监听 */
void Socket::listen() {
    int listen_res = ::listen(fd, SOMAXCONN);
    err_if(listen_res == -1, "socket listen fd error");
}

/* 生成三次握手后的客户端fd */
int Socket::accept(InetAddr *inet_addr) {
    int client_fd = ::accept(fd, (sockaddr *) &inet_addr->addr, &inet_addr->addr_len);
    err_if(client_fd == -1, "socket accept fd error");
    return client_fd;
}