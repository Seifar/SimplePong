//
// Created by Thomas Frank on 2019-04-23.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>
#include "SocketWindow.h"

SocketWindow::SocketWindow(Pong *modell) {
    this->modell = modell;
    connectTo(IP, CLIENT_PORT);
}


void SocketWindow::sendLoop() {
    while (!shouldStop) {
        std::string msg = createStateMsg();
        send(fd, msg.c_str(), msg.length(), 0);
        usleep(SLEEP_TIME_US);
    }
}

void SocketWindow::reveiceLoop() {
    char buffer[BUFFER_SIZE];

    while (!shouldStop) {
        int read = recv(fd, buffer, sizeof(buffer), 0);
        if (!read && !shouldStop) {
            std::cout << "SocketWindow unable to receive!" << std::endl;
            stop();
        }

        std::cout << buffer << std::endl;
        usleep(SLEEP_TIME_US);
    }
}

int SocketWindow::connectTo(std::string ip, int port) {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        std::cout << "Creating socket failed!";
        return -1;
    }

    struct sockaddr_in serv_addr = {0};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(CLIENT_PORT);
    if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0) {
        std::cout << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    if (connect(fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "Connection Failed " << std::endl;
        std::cout << errno << std::endl;
        if(errno == ECONNREFUSED)
            std::cout << "FOOOO";
        return -1;
    }
    return 0;
}

void SocketWindow::stop() {
    shouldStop = true;
}

std::string SocketWindow::createStateMsg() {
    std::stringstream ret;
    auto ballPos = modell->getBallPos();

    ret << "PONG STATE" << std::endl;
    ret << "BALL:" << ballPos.first << "," << ballPos.second << std::endl;
    ret << "P1:" << modell->getPositionP1() << std::endl;
    ret << "P2:" << modell->getPositionP2() << std::endl;
    return ret.str();
}

SocketWindow::~SocketWindow() {
    stop();
    sleep(1);
    close(fd);
}


