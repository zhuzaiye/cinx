// Copyright (c) 2023/11/6 by hzzhu92
//

#include <arpa/inet.h>  // 包含了<netinet/in.h>,不用再次引入

#ifndef INETADDRESS_H
#define INETADDRESS_H

class InetAddress {
public:
    struct sockaddr_in addr; // 地址结构
    socklen_t addr_len;      // 地址长度

    InetAddress();

    InetAddress(const char *ip, uint16_t port);

    ~InetAddress();  // 析构函数的默认作用
};

#endif //INETADDRESS_H
