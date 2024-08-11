// Copyright (c) 2023/11/5 by hzzhu92
// util.cpp

#include <cstdio>
#include <cstdlib>

#include "util.h"

void errif(bool condition, const char *errmsg) {
  if (condition) {
      // perror()函数用于打印错误消息,将标准错误中定义的错误值errno解释为错误消息并打印到标准错误输出流stderr
    perror(errmsg);
    exit(EXIT_FAILURE);
  }
}

