// Copyright (c) 2023/11/22 by hzzhu92
// Server.h

#ifndef SERVER_H
#define SERVER_H

class EventLoop;

class Socket;

class Server {
private:
    EventLoop *loop;
public:
    Server(EventLoop *);

    ~Server();

    void handle_read_event(int);

    void new_connection(Socket *);
};

#endif //SERVER_H
