// Copyright (c) 2023/11/4 by hzzhu92
// client.cpp

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include "util.h"

#define BUFFER_SIZE 1024

int main() {
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    errif(socket_fd == -1, "socket create error");

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8888);

    errif(connect(socket_fd, (sockaddr *) &serv_addr, sizeof(serv_addr)) == -1, "socket connect error");

    while (true) {
        // char buf[1024];  // primitive socket set
        char buff[BUFFER_SIZE]; // epoll socket set
        bzero(&buff, sizeof(buff));
        scanf("%s", buff);
        ssize_t write_bytes = write(socket_fd, buff, sizeof(buff));
        if (write_bytes == -1) {
            printf("socket already disconnected, can't write any more!\n");
            break;
        }

        bzero(&buff, sizeof(buff));
        ssize_t read_bytes = read(socket_fd, buff, sizeof(buff));
        if (read_bytes > 0) {
            printf("message from server: %s\n", buff);
        } else if (read_bytes == 0) {  //
            printf("server socket disconnected!\n");
            break;
        } else if (read_bytes == -1) {  // 读取错误就关闭当前客户端连接
            errif(true, "socket read error");
            close(socket_fd);
        }
    }

    close(socket_fd);

    return 0;
}