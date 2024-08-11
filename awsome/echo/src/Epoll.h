// Copyright (c) 2023/11/7 by hzzhu92
// Epoll.h

#ifndef EPOLL_H
#define EPOLL_H

#include <sys/epoll.h>
#include <vector>

class Channel;

class Epoll {
 private:
    int epfd;     // epoll文件描述符
    struct epoll_event *events;
 public:
    Epoll();
    ~Epoll();

    void add_fd(int fd, uint32_t op) const;
    std::vector<epoll_event> poll_vec(int timeout = -1);

    std::vector<Channel *> poll(int timeout = -1);
    void update_channel(Channel *) const;

};

#endif //EPOLL_H

/**
 * typedef union epoll_data
 *   {
 *     void *ptr;
 *     int fd;
 *     uint32_t u32;
 *     uint64_t u64;
 *   } epoll_data_t;
 *
 *   struct epoll_event
 *   {
 *     uint32_t events;	// Epoll events
 *     epoll_data_t data;	// User data variable
 *   } __EPOLL_PACKED;
 *
 *  epoll是一个红黑树的数据结构
 *  epoll_data 是一个union类型(需要熟悉union类型)
 *
 *
 * */
