// Copyright (c) 2023/11/22 by hzzhu92
// EventLoop.h

#ifndef EVENTLOOP_H
#define EVENTLOOP_H

class Epoll;

class Channel;

class EventLoop {
private:
    Epoll *ep;
    bool quit;
public:
    EventLoop();
    ~EventLoop();

    void loop();
    void update_channel(Channel *);
};

#endif //EVENTLOOP_H
