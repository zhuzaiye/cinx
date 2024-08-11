// Copyright (c) 2024/8/11 by hzzhu92
//

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
