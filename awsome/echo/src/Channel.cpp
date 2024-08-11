// Copyright (c) 2023/11/12 by hzzhu92
// Channel.cpp

#include <sys/epoll.h>

#include "Epoll.h"
#include "Channel.h"
#include "EventLoop.h"

//Channel::Channel(Epoll *_ep, int _fd) : ep(_ep), fd(_fd), events(0), r_events(0), in_epoll(false) {}

Channel::Channel(EventLoop *_loop, int _fd) : loop(_loop), fd(_fd), events(0), r_events(0), in_epoll(false) {}

Channel::~Channel() = default;

void Channel::handleEvent() {
    callback();
}

void Channel::enable_reading() {
    events = EPOLLIN | EPOLLET;
    // ep->update_channel(this);
    loop->update_channel(this);
}

int Channel::get_fd() const {
    return fd;
}

uint32_t Channel::get_events() const {
    return events;
}

uint32_t Channel::get_r_events() const {
    return r_events;
}

bool Channel::get_in_epoll() const {
    return in_epoll;
}

void Channel::set_in_epoll() {
    in_epoll = false;
}

void Channel::set_r_events(uint32_t _ev) {
    r_events = _ev;
}

void Channel::set_callback(std::function<void()> _cb) {
//    callback = std::move(_cb);
    callback = _cb;
}


