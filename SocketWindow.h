//
// Created by Thomas Frank on 2019-04-23.
// This class is the Interface to the Pong game over a TCP socket
//

#ifndef PONG_SOCKETWINDOW_H
#define PONG_SOCKETWINDOW_H


#include "Pong.h"

#define IP "127.0.0.1"
#define CLIENT_PORT 8080
#define BUFFER_SIZE 1024
#define SLEEP_TIME_US 100

class SocketWindow {
private:
    Pong *modell;
    int fd;

    int connectTo(std::string ip, int port);

    bool shouldStop = false;

public:
    SocketWindow(Pong *modell);

    ~SocketWindow();

    void sendLoop();

    void reveiceLoop();

    void stop();

    std::string createStateMsg();
};


#endif //PONG_SOCKETWINDOW_H
