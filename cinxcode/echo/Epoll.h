// Copyright (c) 2023/11/7 by hzzhu92
//

#include <sys/epoll.h>
#include <vector>

#ifndef EPOLL_H
#define EPOLL_H

class Epoll {
private:
    int epfd;
    struct epoll_event *events;
public:
    Epoll();

    ~Epoll();

    void add_fd(int fd, uint32_t op);

    std::vector<epoll_event> poll(int timeout = -1);
};

#endif //EPOLL_H
