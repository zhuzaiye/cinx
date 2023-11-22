// Copyright (c) 2023/11/21 by hzzhu92
// channel.h

#ifndef CHANNEL_H
#define CHANNEL_H

#include <sys/epoll.h>
#include <functional>

class EventLoop;

class Channel {
private:
    EventLoop *loop;
    int fd;

    uint32_t events;
    uint32_t r_events;

    bool in_epoll;

    std::function<void()> callback;
public:
    Channel(EventLoop *_loop, int _fd);

    ~Channel();

    int get_fd();

    uint32_t get_events();

    uint32_t get_r_events();

    void set_r_event(uint32_t);

    void handle_event();

    void enable_reading();

    void set_callback(std::function<void()>);

    bool get_in_epoll();

    void set_in_epoll();
};

#endif //CHANNEL_H
