// Copyright (c) 2023/11/6 by hzzhu92
// Socket.h

#ifndef SOCKET_H
#define SOCKET_H

#include "InetAddress.h"

class Socket {
private:
    int fd;   // socket文件描述
public:
    Socket();

    // explicit 防止隐式转换, 即explicit构造函数必须按照设定的方式进行显式调用
    explicit Socket(int);

    ~Socket();

    void bind(InetAddress *) const;  // 将fd和地址绑定

    void listen() const;

    void set_nonblocking() const;

    int accept(InetAddress *) const;

    int get_fd() const;
};

#endif //SOCKET_H

/**
 * explicit 的例子
 *
 * class String {
 * public:
 *  explicit String(int n);
 *  String(const char* p);
 * };
 *
 *
 * String s1 = 'a';  // 错误, 不能做隐式char->String转换
 * String s2(10);    // 可以, 调用explicit String(int n)
 * String s3 = String(10);//可以：调用explicit String(int n);再调用默认的复制构造函数
 * String s4 = "Brian"; //可以：隐式转换调用String(const char *p);再调用默认的复制构造函数
 * String s5("Fawlty"); //可以：正常调用String(const char *p);
 *
 * void f(String);
 * String g() {
 *  f(10);        // 错误, 不能做隐式int->String转换
 *  f("Arthur");  // 可以, 隐式转换, 等价于f(String("Arthur"))
 *  return 10;    // 不可以, 无法座岛隐式的将int转黄成String
 * }
 *
 * */
