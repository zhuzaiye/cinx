// Copyright (c) 2024/8/11 by hzzhu92
//

#include "src/EventLoop.h"
#include "src/Server.h"

int main() {
    EventLoop *loop = new EventLoop();
    Server *server = new Server(loop);
    loop->loop();
    return 0;
}