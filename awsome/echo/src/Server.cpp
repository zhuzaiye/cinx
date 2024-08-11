// Copyright (c) 2024/8/11 by hzzhu92
//

#include <functional>
#include <unistd.h>
#include <cstring>

#include "Server.h"
#include "Socket.h"
#include "InetAddress.h"
#include "Channel.h"

#define READ_BUFFER 1024

Server::Server(EventLoop *_loop) : loop(_loop) {
    Socket *serv_sock = new Socket();
    InetAddress *serv_addr = new InetAddress("127.0.0.1", 8888);
    serv_sock->bind(serv_addr);
    serv_sock->listen();
    serv_sock->set_nonblocking();

    Channel *serv_channel = new Channel(loop, serv_sock->get_fd());
    std::function<void()> cb = std::bind(&Server::new_connection, this, serv_sock);
    serv_channel->set_callback(cb);
    serv_channel->enable_reading();
}

Server::~Server() {}

void Server::handle_read_event(int sock_fd) {
    char buf[READ_BUFFER];
    while (true) {
        bzero(&buf, sizeof(buf));
        ssize_t bytes_read = read(sock_fd, buf, sizeof(buf));
        if (bytes_read > 0) {
            printf("message from client fd %d: %s\n", sock_fd, buf);
            write(sock_fd, buf, sizeof(buf));
        } else if (bytes_read == -1 && errno == EINTR) {  //客户端正常中断、继续读取
            printf("continue reading");
            continue;
        } else if (bytes_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))) { //非阻塞IO，这个条件表示数据全部读取完毕
            printf("finish reading once, errno: %d\n", errno);
            break;
        } else if (bytes_read == 0) {  //EOF，客户端断开连接
            printf("EOF, client fd %d disconnected\n", sock_fd);
            close(sock_fd);   //关闭socket会自动将文件描述符从epoll树上移除
            break;
        }
    }
}

void Server::new_connection(Socket *serv_sock) {
    InetAddress *clnt_addr = new InetAddress();
    Socket *clnt_sock = new Socket(serv_sock->accept(clnt_addr));
    printf("new client fd %d! IP: %s Port: %d\n",
           clnt_sock->get_fd(),
           inet_ntoa(clnt_addr->addr.sin_addr),
           ntohs(clnt_addr->addr.sin_port));
    clnt_sock->set_nonblocking();
    Channel *clnt_channel = new Channel(loop, clnt_sock->get_fd());
    std::function<void()> cb = std::bind(&Server::handle_read_event, this, clnt_sock->get_fd());
    clnt_channel->set_callback(cb);
    clnt_channel->enable_reading();
}
