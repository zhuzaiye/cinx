// Copyright (c) 2023/11/21 by hzzhu92
// InetAddr.cpp

#include <cstring>
#include "InetAddr.h"

InetAddr::InetAddr() : addr_len(sizeof(addr)) {
    bzero(&addr, sizeof(addr));
}

InetAddr::InetAddr(const char *ip, uint16_t port) : addr_len(sizeof(addr)) {
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    addr_len = sizeof(addr);
}

InetAddr::~InetAddr() = default;