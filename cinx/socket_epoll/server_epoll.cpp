// Copyright (c) 2023/11/4 by hzzhu92
// server_epoll.cpp

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <cerrno>
#include "util.h"

#define MAX_EVENTS 1024
#define READ_BUFFER 1024

void set_nonblock(int fd) {
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

/**
 * 1. 创建socket_fd
 * 2. 创建epoll_fd
 * 3. 将socket_fd注册到epoll_fd
 *  只要socket_fd接受到一个新的客户端连接[发生可读事件], accept新客户端并将客户端的socket_fd加入epoll
 *  epoll会监听这个客户端socket_fd是否有事件发生, 如果有就处理事件, 没有并超时将
 * */

int main() {
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    errif(socket_fd == -1, "socket create error");

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8888);

    errif(bind(socket_fd, (sockaddr *) &serv_addr, sizeof(serv_addr)) == -1, "socket bind error");

    errif(listen(socket_fd, SOMAXCONN) == -1, "socket listen error");

    // epoll_create创建epoll文件描述符
    // 向操作系统请求创建保存epoll事件的文件描述符空间
    int epoll_fd = epoll_create1(0);
    errif(epoll_fd == -1, "epoll create error");

    // epoll通过epoll_event将发生事件的文件描述进行集中, 并交给epoll_wait进行监控
    struct epoll_event events[MAX_EVENTS], ev;
    bzero(&events, sizeof(events));
    bzero(&ev, sizeof(ev));
    // EPOLLIN: 实现读取数据功能
    // EPOLLET: 以边缘触发的方式得到事件通知
    ev.events = EPOLLIN | EPOLLET;  // 这个是否需要设置为ET模式?
    // 设定event的IO为socket_fd
    ev.data.fd = socket_fd;

    // 将套接字改为非阻塞模式
    set_nonblock(socket_fd);
    // epoll_ctl请求操作系统添加或者删除监视对象文件描述符
    // epfd: epoll文件描述符
    // op: 对指定监视对象的添加,删除或者修改操作
    // fd: 需要注册的监视对象文件描述符
    // event: 监视对象的事件类型
    // epoll_ctl(A, ADD_op, B, C): epoll例程A中注册文件描述符B, 目的是监视参数C中的事件
    // epoll_ctl(A, DEL_op, B, NULL): epoll例程A中删除文件描述符B
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &ev);

    // 监听epoll上的事件
    while (true) {
        // epoll_wait获取事件发生的fd
        // epfd: epoll文件描述符
        // events: 保存发生事件的文件描述符集合的结构体地址值
        // maxevents: 可以保存的最大事件数
        // timeout: 以1/1000秒为单位的等待时间, 为-1时, 这表示一致等待直到发生事件
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1); // 如果有nfds个fd发生事件
        if (nfds == -1) {
            errif(true, "epoll wait error");
            break;
        }

        for (int i = 0; i < nfds; ++i) {  // 处理nfds个事件
            if (events[i].data.fd == socket_fd) {  // 发生事件的fd是服务器socket_fd, 表示有新客户端连接
                // 创建客户端client_sock_fd并接受客户端数据
                struct sockaddr_in client_addr;
                socklen_t client_addr_len = sizeof(client_addr);
                bzero(&client_addr, client_addr_len);

                int client_sock_fd = accept(socket_fd, (sockaddr *) &client_addr, &client_addr_len);
                errif(client_sock_fd == -1, "socket accept error");

                printf("new client fd %d! IP: %s Port:%d\n", client_sock_fd, inet_ntoa(client_addr.sin_addr),
                       ntohs(client_addr.sin_port));

                bzero(&ev, sizeof(ev));
                ev.data.fd = client_sock_fd;
                ev.events = EPOLLIN | EPOLLET;
                set_nonblock(client_sock_fd);
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_sock_fd, &ev);  //将客户段的socket_fd添加到epoll
            } else if (events[i].events & EPOLLIN) {  // 发生事件的是客户端, 并且是可读事件(EPOLLIN)
                char buff[READ_BUFFER];
                while (true) { // 由于使用非阻塞IO,需要不断读取,直到全部读取完毕
                    bzero(&buff, sizeof(buff));
                    ssize_t read_bytes = read(events[i].data.fd, buff, sizeof(buff)); // 处理该fd上发生的事件
                    if (read_bytes > 0) {
                        printf("message from client fd %d: %s\n", events[i].data.fd, buff);
                        write(events[i].data.fd, buff, sizeof(buff));
                    } else if (read_bytes == 0) {  // EOF, 客户端断开连接
                        printf("EOF, client fd %d disconnected\n", events[i].data.fd);
                        close(events[i].data.fd);  // 关闭socket, 自动将事件fd从epoll红黑树上移除
                        break;
                    } else if (read_bytes == -1 && errno == EINTR) { // 客户端正常终端, 继续读取
                        printf("continue reading");
                        continue;
                    } else if (read_bytes == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))) { // 非阻塞IO,数据全部读取完毕
                        // 该fd上数据读取完毕
                        printf("finish reading once, errno: %d\n", errno);
                        break;
                    }
                }
            } else {
                printf("something else happened\n");
            }
        }
    }

    close(socket_fd);
    close(epoll_fd);

    return 0;
}

/**
 * 水平触发和边缘触发
 *
 * 区别点: 发生事件的时间点
 *
 * LT水平触发: 只要输入缓冲有数据就会一直通知内核处理该事件. 所以只要缓冲区存在数据,就会在每次读取的时候注册事件
 * ET边缘触发: 输入缓冲收到数据时仅注册1次事件, 输入缓冲中还有数据, 就不会在进行注册
 * */