// Copyright (c) 2023/11/21 by hzzhu92
// InetAddr.h

#ifndef INETADDR_H
#define INETADDR_H

/**
 * 对于依赖于特定库的头文件，最好将相关的包含语句放在头文件中。
 * 这确保了头文件的用户在使用该头文件时不需要关心其依赖关系，而是能够直接获得所需的声明。
 * 有助于确保头文件的用户不会因为遗漏依赖关系而遇到编译错误。
 * 同时，也提高了代码的可维护性，因为头文件中包含了它所依赖的所有必要信息。
 *
 * */

#include <arpa/inet.h>

class InetAddr {
public:
    InetAddr();
    InetAddr(const char* ip, uint16_t port);
    ~InetAddr();

    socklen_t addr_len;
    struct sockaddr_in addr;
};

#endif //INETADDR_H
