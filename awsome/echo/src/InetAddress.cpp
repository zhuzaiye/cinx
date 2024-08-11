// Copyright (c) 2023/11/6 by hzzhu92
//
// 应该吧c和c++区分开来
// 写代码要清楚自己是写的c还是c++
// c就引入c的头文件, c++就引入c++的头文件
#include <cstring>

#include "InetAddress.h"

// 一定要初始换addr结构体, 确定对象使用前已被初始化
InetAddress::InetAddress() : addr(), addr_len(sizeof(addr)) {
    bzero(&addr, sizeof(addr));
}

InetAddress::InetAddress(const char *ip, uint16_t port) : addr(), addr_len(sizeof(addr)) {
    bzero(&addr, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    addr_len = sizeof(addr);
}

InetAddress::~InetAddress()= default;;