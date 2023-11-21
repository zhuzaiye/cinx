# Make CPP Server

## 概述理解

- 网络编程: 如何通过网络协议和软件技术实现计算机实体之间进行高效安全完整的数据传递交换.
- SOCKET: 网络传输交换数据的软件设备.
- 步骤: 如下

| Step   | Func                                                            | DESC                       |
|--------|-----------------------------------------------------------------|----------------------------|
| Step 1 | `socket(int domain, int type, int protocol)`                    | 通过`socket`软件技术创建网络数据交换文件实体--买电话|
| Step 2 | `bind(int sockfd, struct socksaddr* addr, socketlen_t addrlen)` | 给`socket`网络文件绑定数据交换识别地址--买号码并插卡|
| Step 3 | `listen(int sockfd, int backlog)`                               | 启动`socket`实体监听程序--开机并出现信号  |
| Step 3 | `accpet(int sockfd, struct socksaddr* addr, socketlen_t addrlen)`| 从`socket`实体获取传输内容--来电并接听电话 |

## socket

- `socket(IPv4/IPv6, TCP/UDP, 0)`: 创建socket套接字, 获取listen_socket_fd
- `bind(listen_socket_fd, 服务器地址, 服务器地址长度)`: 给listen_socket_fd绑定服务器地址
- `listen(listen_socket_fd, size)`: 开启listen_socket_fd的socket监听服务
- `accept(listen_socket_fd, 客户端信息, len)`: 客户端connect()后, 与服务端listen_socket_fd三次握手成功后,返回连接描述符conn_fd
- `recv(conn_fd, buff, len)`: 从握手成功的conn_fd读取数据[read()]
- `send(conn_fd, buff, len)`: 向握手成功的conn_fd写入数据, 以回应客户端[write()]

```c
#include <sys/socket.h>

// 创建listen_socket_fd
int listen_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
// 给listen_socket_fd绑定服务器地址
bind(listen_socket_fd, (sockaddr *) &serv_addr, sizeof(serv_addr))
// 开启listen_socket_fd的监听, 并设置最大连接数量
listen(listen_socket_fd, SOMAXCONN)
// listen_socket_fd受理请求队列中的连接, 返回还是socket文件描述符conn_fd
int conn_fd = accept(socket_fd, (sockaddr *) &client_addr, &client_addr_len);
```

## epoll

- `epoll_create()`: 创建epoll_fd, epollitem的红黑树和就绪列表
- `epoll_ctl(epoll_fd, op, socket_fd, event_type)`: 将socket_fd加入epoll[listen_fd和conn_fd都只需要从用户态拷贝到内核态, 一次]
- `while(true)`: 循环监听
- `epoll_wait()`: 将就绪队列从内核拷贝带用户态[从内核态拷贝到用户态只要拷贝就绪事件]
- `for()`: 遍历就绪队列[而不是遍历全部socket_fd]
  - 如果是`listen_fd`有可读事件,就将`conn_fd`加入`epoll`
  - 如果是`conn_fd`有可读事件, 读取数据, 并`send()`, 读完就从`epoll`中移除,并关闭该`conn_fd`

## func

- `memset`和`bzero`

> bzero和memset函数都可以用来进行内存清零操作
> 如果只是简单的将内存清零, 可以使用bzero函数
> 如果需要将内存区域设置为其他值, 或者需要判断操作是否成功,可以使用memset函数

```c
#include <cstring>

// s为要清零的内存区域的起始地址, n为要清零的字节数
// 等同于memset将值设置为0, 将内存区域全部设置为0
void bzero(void *s, size_t n);

// s为要设置的内存区域的起始地址, c为要设置的值，n为要设置的字节数
// memset函数的作用是将s所指向的内存区域的前n个字节都设置为值c
// 返回指向内存区域的指针, 可以通过指针返回值判断操作是否成功
void *memset(void *s, int c, size_t n);
```

- `htonl, ntohl, htons, ntohs`

> 用来将主机字节顺序转换为网络字节顺序, HBO-->NBO
> BO: byte order 字节顺序
> NBO: 网络字节顺序, 从高到低的顺序存储,使用统一的网络字节顺序, 避免兼容问题
> HBO: 主机字节顺序, intel和IBM的大小端问题, 需要转换成网络字节顺序便于解析

```c
// htonl() -- Host to Network Long
// htons() -- Host to Network Short
// ntohl() -- Network to Host Long
// ntohs() -- Network to Host Short

#include <arpa/inet.h>
```