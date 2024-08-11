// Copyright (c) 2024/8/11 by hzzhu92
//

#include <vector>

#include "EventLoop.h"
#include "Epoll.h"
#include "Channel.h"

EventLoop::EventLoop() : ep(nullptr), quit(false) {
    ep = new Epoll();
}

EventLoop::~EventLoop() {
    delete ep;
}

// loop() 开始事件驱动,即调用epoll_wait()函数的死循环
void EventLoop::loop() {
    while (!quit) {
        std::vector<Channel *> chs;
        chs = ep->poll();
        for (auto &ch : chs) {
            ch->handleEvent();
        }
    }
}

void EventLoop::update_channel(Channel *ch) {
    ep->update_channel(ch);
}