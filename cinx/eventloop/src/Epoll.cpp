// Copyright (c) 2023/11/22 by hzzhu92
// Epoll.cpp

#include <cstring>
#include <unistd.h>
#include "Epoll.h"
#include "Channel.h"
#include "util.h"

#define MAX_EVENTS 1000

Epoll::Epoll() : epfd(-1), events(nullptr) {
    epfd = epoll_create1(0);
    err_if(epfd == -1, "epoll create error");
    events = new epoll_event[MAX_EVENTS];  /* 申明指定量的epoll事件event slice */
    bzero(events, sizeof(*events) * MAX_EVENTS);  /* 初始化epoll事件event slice */
}

Epoll::~Epoll() {
    if (epfd != -1) {
        close(epfd);
        epfd = -1;
    }
    delete[] events;
}

void Epoll::add_fd(int fd, uint32_t op) {
    struct epoll_event ev;
    bzero(&ev, sizeof(ev));
    ev.data.fd = fd;
    ev.events = op;
    err_if(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1, "epoll add event error");
}

std::vector<Channel *> Epoll::poll(int timeout) {
    std::vector<Channel *> active_channels;
    int nfds = epoll_wait(epfd, events, MAX_EVENTS, timeout);
    err_if(nfds == -1, "epoll wait error");
    for (int i = 0; i < nfds; ++i) {
        Channel *ch = (Channel *) events[i].data.ptr;
        ch->set_r_event(events[i].events);
        active_channels.push_back(ch);
    }
    return active_channels;
}

void Epoll::update_channel(Channel *chan) {
    int fd = chan->get_fd();
    struct epoll_event ev;
    bzero(&ev, sizeof(ev));
    ev.data.ptr = chan;
    ev.events = chan->get_events();
    if (!chan->get_in_epoll()) {
        err_if(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1, "epoll add chan error");
        chan->set_in_epoll();
    } else {
        err_if(epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev) == -1, "epoll mod chan error");
    }
}