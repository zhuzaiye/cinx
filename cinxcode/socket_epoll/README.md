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


## echo

> socket 基础