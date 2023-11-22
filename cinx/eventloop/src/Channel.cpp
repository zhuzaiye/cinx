// Copyright (c) 2023/11/21 by hzzhu92
// channel.cpp

#include <utility>
#include "Channel.h"
#include "EventLoop.h"

Channel::Channel(EventLoop *_loop, int _fd) : loop(_loop), fd(_fd), events(0), r_events(0), in_epoll(false) {}

Channel::~Channel() = default;

int Channel::get_fd() {
    return fd;
}

uint32_t Channel::get_events() {
    return events;
}

uint32_t Channel::get_r_events() {
    return r_events;
}

bool Channel::get_in_epoll() {
    return in_epoll;
}

void Channel::set_in_epoll() {
    in_epoll = false;
}

void Channel::set_r_event(uint32_t _ev) {
    r_events = _ev;
}

void Channel::handle_event() {
    callback();
}

void Channel::enable_reading() {
    events = EPOLLIN | EPOLLET;
    loop->update_channel(this);
}

void Channel::set_callback(std::function<void()> _cb) {
    // callback = _cb;
    /* */
    callback = std::move(_cb);
}
