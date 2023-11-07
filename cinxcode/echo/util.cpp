// Copyright (c) 2023/11/5 by hzzhu92
// util.cpp

#include "util.h"
#include <cstdio>
#include <cstdlib>

void errif(bool condition, const char *errmsg) {
    if (condition) {
        perror(errmsg);
        exit(EXIT_FAILURE);
    }
}

