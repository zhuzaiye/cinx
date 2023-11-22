// Copyright (c) 2023/11/22 by hzzhu92
// Epoll.h

#ifndef EPOLL_H
#define EPOLL_H

#include <sys/epoll.h>
#include <vector>

class Channel;

class Epoll {
private:
    int epfd;
    struct epoll_event *events;
public:
    Epoll();
    ~Epoll();

    void add_fd(int fd, uint32_t op);
    void update_channel(Channel *);
    std::vector<Channel *> poll(int timeout = -1);
};

#endif //EPOLL_H
