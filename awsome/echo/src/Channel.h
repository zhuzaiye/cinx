// Copyright (c) 2023/11/12 by hzzhu92
// channel.h

#ifndef CHANNEL_H
#define CHANNEL_H

#include <functional>

class EventLoop;

// 预置类声明引用 只能用于指针
class Epoll;

class Channel {
 private:
    // Epoll *ep;         // Epoll类
    EventLoop *loop;   //
    int fd;            // Channel负责的文件描述符

    uint32_t events;   // 指定监听文件描述符的事件, 用于针对不同事件采取不同的处理方式
    uint32_t r_events; // 表示epoll返回该channel时文件描述符正在发生的事件
    bool in_epoll;     // 表示当前channel是否已经在epoll红黑树中,为了在注册Channel时候区分使用EPOLL_CTL_ADD还是EPOLL_CTL_MOD
    std::function<void()> callback;  // 回调函数
 public:
    // Channel(Epoll *_ep, int _fd);
    Channel(EventLoop *_loop, int _fd);
    ~Channel();

    void handleEvent();
    void enable_reading();

    int get_fd() const;  // const用于表明该函数只能读取数据成员, 不能修改数据成员; 无const修饰说明函数可读可写数据成员
    uint32_t get_events() const;
    uint32_t get_r_events() const;
    bool get_in_epoll() const;

    void set_in_epoll();
    void set_r_events(uint32_t);
    void set_callback(std::function<void()>);
};

#endif //CHANNEL_H
