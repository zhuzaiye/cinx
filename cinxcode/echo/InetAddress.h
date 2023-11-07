// Copyright (c) 2023/11/6 by hzzhu92
//

#include <arpa/inet.h>

#ifndef INETADDRESS_H
#define INETADDRESS_H

class InetAddress {
public:
    struct sockaddr_in addr{}; // 初始化
    socklen_t addr_len;

    InetAddress();

    InetAddress(const char *ip, uint16_t port);

    ~InetAddress();
};

#endif //INETADDRESS_H
