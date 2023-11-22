// Copyright (c) 2023/11/21 by hzzhu92
// util.cpp

#include <cstdio>
#include <cstdlib>
#include "util.h"

/**
 * [cstdio] `void perror(const char *s)`: 用于打印与当前`errno`值相关的错误信息到标准错误流(stderr). 其中, s 是一个指向以 null 结尾的字符串的指针，它将被打印在错误消息之前.
 *                                        perror 在输出时会附加一个冒号和一个空格，然后是描述错误的字符串. 即`s: errno`.
 * [cstdlib] `exit(EXIT_FAILURE)`: 程序调用 exit(EXIT_FAILURE) 退出，并返回失败状态码 EXIT_FAILURE。这是一种在程序遇到错误时进行报错并退出的典型做法。
 * */

void err_if(bool cond, const char *err_msg) {
    if (cond) {
        perror(err_msg);
        exit(EXIT_FAILURE);
    }
}
