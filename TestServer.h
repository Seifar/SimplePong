//
// Created by Thomas Frank on 2019-04-05.
//

#ifndef PONG_TESTSERVER_H
#define PONG_TESTSERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <thread>
#include <poll.h>

#define SERVER_PORT 8080


class TestServer {
private:
    std::thread internalThread;

    struct sockaddr_in address;
    //connections[0] is server socket
    std::vector<struct pollfd> connections;
    int *serverSocket;

    bool shouldExit;

    void run();

public:
    TestServer();

    ~TestServer();

    // non-blocking; will exit server soon
    void terminate();
};


#endif //PONG_TESTSERVER_H
