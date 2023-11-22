// Copyright (c) 2023/11/21 by hzzhu92
// Socket.h

#ifndef SOCKET_H
#define SOCKET_H

class InetAddr;

class Socket {
private:
    int fd;
public:
    Socket();
    Socket(int);
    ~Socket();

    int get_fd();
    void set_nonblocking();

    void bind(InetAddr *);
    void listen();
    int accept(InetAddr *);
};

#endif //SOCKET_H
