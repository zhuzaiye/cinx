// Copyright (c) 2023/11/6 by hzzhu92
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <unistd.h>  // read和write对网络接口的数据进行读写
#include "src/util.h"

#define BUFFER_SIZE 1024

int main() {
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    errif(sock_fd == -1, "socket create error");

    struct sockaddr_in serv_addr = {};
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8888);

    errif(connect(sock_fd, (sockaddr *) &serv_addr, sizeof(serv_addr)) == -1, "socket connect error");

    while (true) {
        char buf[BUFFER_SIZE];
        bzero(&buf, sizeof(buf));  // 清空缓冲区
        scanf("%s", buf);
        ssize_t write_bytes = write(sock_fd, buf, sizeof(buf));  // 发送数据到服务器socket,返回已发送数据大小
        printf("input: %s\n", buf);
        if (write_bytes == -1) {
            printf("socket already disconnected, can't write any more!\n");
            break;
        }

        bzero(&buf, sizeof(buf));
        ssize_t read_bytes = read(sock_fd, buf, sizeof(buf));  // 读取服务器socket返回到缓冲区
        if (read_bytes > 0) {
            printf("message from server: %s\n", buf);
        } else if (read_bytes == 0) {  // read返回0, 表示EOF
            printf("server socket disconnected!\n");
            break;
        } else if (read_bytes == -1) {  // 服务器socket错误
            close(sock_fd);
            errif(true, "socket read error");
        }
    }
    close(sock_fd);
    return 0;
}