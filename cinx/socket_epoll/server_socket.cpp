// Copyright (c) 2023/11/4 by hzzhu92
// server.cpp
// 参考<<TCP/IP网络编程>> -- 韩圣雨
// 采用TCP/IP协议(4层网络模型, 应用层-->传输层[TCP/UDP]-->网)

#include <cstdio>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include "util.h"

/**
 * socket 是双全工方式工作的[即可以双向传递数据]
 *
 * 连接
 * 第一次握手 (SYN)[SEQ 1000, ACK -] A-->B {首次连接, A:SEQ1000向B传输数据包初始号段, A:SEQ1000请B允许向其传输序号1001数据包.}
 * 第二次握手 (SYN+ACK)[SEQ 2000, ACK 1001] A<--B {B:SEQ2000请A允许向其传输2001数据包, B:ACK1001是B接受A:SEQ1000成功,请A向B传输其1001号端数据包 }
 * 第三次握手 (ACK)[SEQ 1001, ACK 2001] A<-->B {A:SEQ1001数据包发送至B, 并A:ACK2001通知B已收到2000数据包, B可以向A传输2001号段数据包. 完成双向握手,双方传输就绪}
 *
 * 数据交换
 * 后续传递 SEQ和ACK交替出现, ACK=SEQ+传递字节数+1, 保证超时等情况下数据包完整传输
 *
 * 断开
 * 第一次 (FIN)[SEQ 5000, ACK -] A-->B {A:SEQ5000向B发出结束连接绘画请求}
 * 第二次 (ACK)[SEQ 7500, ACK 5001] A<--B {B:SEQ7500向A发出ACK:5001 结束连接的确认}
 * 第三次 (FIN)[SEQ 7501, ACK 5001] A<--B {B并顺带二次ACK向A发出FIN的断开请求}
 * 第四次 (ACK)[SEQ 5001, ACK 7502] A-->B {A向B返回数据传输完整并可以断开}
 * */

int main() {
    // 初始化socket文件
    // AF_INET: 网络曾协议 IPV4
    // SOCK_STREAM: 传输层协议 TCP
    // 返回socket在LINUX操作系统的IO文件代号(大于3)
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    errif(socket_fd == -1, "socket create error");

    struct sockaddr_in serv_addr;  // 地址初始化 ip:port
    bzero(&serv_addr, sizeof(serv_addr));  // 初始化serve_addr所有成员
    serv_addr.sin_family = AF_INET;  // 指定网络地址协议 IPV4 AF_INET6:IPV6
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // 基于字符串的地址给定 inet_addr转换字符串为sockaddr_in的s_addr的32位整数类型并检测无效IP地址
    serv_addr.sin_port = htons(8888);  // 端口给定,统一网络字节序(CPU大端小端原因, 约定统一使用大端) htons: 将short数据从主机字节序转化位网络约定的字节序

    // 服务端通过bind将socket完整准备操作
    // 客户端则是通过connect完成socket的完整准备操作
    errif(bind(socket_fd, (sockaddr *) &serv_addr, sizeof(serv_addr)) == -1, "socket bind error");
    // listen是socket的启动, 实现socket的等待连接状态, 即受理客户端连接前的状态
    // 存在一个客户端请求连接的队列缓存, 最小15, 超过最大连接数, 客户端连接服务端的请求都要阻塞
    // listen成功后才能受理客户端请求
    errif(listen(socket_fd, SOMAXCONN) == -1, "socket listen error");

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    bzero(&client_addr, client_addr_len);

    // accept是受理连接请求等待队列中待处理的客户端请求, accept在没有任何请求连接时会处于阻塞状态
    // accept函数内部将产生用于I/O的套接字, 返回的socket文件描述符, 数据将接受到client_socket_fd中
    // accept将socket_fd等待队列中的客户端连接取出,并将此链接的信息通过I/O回填到socket_add结构的socket文件中
    int client_sock_fd = accept(socket_fd, (sockaddr *) &client_addr, &client_addr_len);
    errif(client_sock_fd == -1, "socket accept error");

    printf("new client fd %d! IP: %s Port:%d\n", client_sock_fd, inet_ntoa(client_addr.sin_addr),
           ntohs(client_addr.sin_port));

    while (true) {
        char buff[1024];
        bzero(&buff, sizeof(buff));
        ssize_t read_bytes = read(client_sock_fd, buff, sizeof(buff));
        if (read_bytes > 0) {
            printf("message from client fd %d: %s\n", client_sock_fd, buff);
            write(client_sock_fd, buff, sizeof(buff));
        } else if (read_bytes == 0) {
            printf("client fd %d disconnected\n", client_sock_fd);
            close(client_sock_fd);
            break;
        } else if (read_bytes == -1) {
            close(client_sock_fd);
            errif(true, "sock read error");
        }
    }

    close(socket_fd);  //

    return 0;
}