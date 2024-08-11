// Copyright (c) 2023/11/7 by hzzhu92
// Epoll.cpp

#include <unistd.h>
#include <cstring>

#include "Epoll.h"
#include "Channel.h"
#include "util.h"

#define MAX_EVENTS 1000

Epoll::Epoll() : epfd(-1), events(nullptr) {
    // 创建epoll句柄
    epfd = epoll_create1(0);
    errif(epfd == -1, "epoll create error");
    events = new epoll_event[MAX_EVENTS];
    bzero(events, sizeof(*events) * MAX_EVENTS);
}

Epoll::~Epoll() {
    if (epfd != -1) {
        close(epfd);
        epfd = -1;
    }
    // 释放events
    delete[] events;
}

void Epoll::add_fd(int fd, uint32_t op) const {
    struct epoll_event ev;
    bzero(&ev, sizeof(ev));
    ev.data.fd = fd;
    ev.events = op;
    errif(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1, "epoll add event error");
}

std::vector<epoll_event> Epoll::poll_vec(int timeout) {
    std::vector<epoll_event> active_events;
    int nfds = epoll_wait(epfd, events, MAX_EVENTS, timeout);
    errif(nfds == -1, "epoll wait error");
    for (int i = 0; i < nfds; ++i) {
        active_events.push_back(events[i]);
    }
    return active_events;
}

std::vector<Channel *> Epoll::poll(int timeout) {
    std::vector<Channel *> active_channels;
    // epoll_wait 获取事件
    int nfds = epoll_wait(epfd, events, MAX_EVENTS, timeout);
    errif(nfds == -1, "epoll wait error");
    for (int i = 0; i < nfds; ++i) {
        Channel *ch = (Channel *) events[i].data.ptr;
        ch->set_r_events(events[i].events);
        active_channels.push_back(ch);
    }
    return active_channels;
}

void Epoll::update_channel(Channel *channel) const {
    int fd = channel->get_fd(); // 获取channel的文件描述符
    struct epoll_event ev = {};
    bzero(&ev, sizeof(ev));
    ev.data.ptr = channel;
    ev.events = channel->get_events();  // 获取channel监听的指定类型事件
    if (!channel->get_in_epoll()) {
        errif(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1, "epoll add error");
        channel->set_in_epoll();
    } else {
        errif(epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev) == -1, "epoll modify error");
    }
}