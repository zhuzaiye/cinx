// Copyright (c) 2023/11/22 by hzzhu92
// EventLoop.cpp

#include "EventLoop.h"
#include "Epoll.h"
#include "Channel.h"
#include <vector>

EventLoop::EventLoop() : ep(nullptr), quit(false) {
    ep = new Epoll();
}

EventLoop::~EventLoop() {
    delete ep;
}

void EventLoop::loop() {
    if (!quit) {
        std::vector<Channel *> chs;
        chs = ep->poll();
        for (auto &ch: chs) {
            ch->handle_event();
        }
    }
}

void EventLoop::update_channel(Channel *ch) {
    ep->update_channel(ch);
}
