// Copyright (c) 2023/11/6 by hzzhu92
//

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>

#include "Socket.h"
#include "util.h"
#include "InetAddress.h"

Socket::Socket() : fd(-1) {
  // ip地址类型, 数据传输方式, 传输协议
  fd = socket(AF_INET, SOCK_STREAM, 0);
  errif(fd == -1, "socket create error");
}

Socket::Socket(int _fd) : fd(_fd) {
  errif(fd == -1, "socket create error");
}

Socket::~Socket() {
  if (fd != -1) {
    close(fd);
    fd = -1;
  }
}

void Socket::bind(InetAddress *addr) const {
  // 同名覆盖
  errif(::bind(fd, (sockaddr *) &addr->addr, addr->addr_len) == -1, "socket bind error");
}

void Socket::listen() const {
  errif(::listen(fd, SOMAXCONN) == -1, "socket listen error");
}

void Socket::set_nonblocking() const {
  fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

int Socket::accept(InetAddress *addr) const {
  int client_fd = ::accept(fd, (sockaddr *) &addr->addr, &addr->addr_len);
  errif(client_fd == -1, "socket accept error");
  return client_fd;
}

int Socket::get_fd() const {
  return fd;
}


/**
 * int Socket::get_fd() const{}
 *
 * 成员函数后面的`const`关键字, 说明该函数不会修改该类实例的成员变量
 * 除非这些成员变量被标记为`mutable`
 *
 * `const`成员函数可以被`const`对象调用, 而非`const`成员函数则不行
 * */