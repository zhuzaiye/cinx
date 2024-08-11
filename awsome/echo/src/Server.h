// Copyright (c) 2024/8/11 by hzzhu92
//

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
    void new_connection(Socket *serv_sock);
};

#endif //SERVER_H
