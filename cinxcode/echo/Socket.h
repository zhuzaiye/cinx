// Copyright (c) 2023/11/6 by hzzhu92
// Socket.h

#include "InetAddress.h"

#ifndef SOCKET_H
#define SOCKET_H

class Socket {
private:
    int fd;
public:
    Socket();

    Socket(int);

    ~Socket();

    void bind(InetAddress *);

    void listen();

    void set_nonblocking();

    int accept(InetAddress *);

    int get_fd();
};

#endif //SOCKET_H
