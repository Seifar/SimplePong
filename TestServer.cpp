//
// Created by Thomas Frank on 2019-04-05.
//

#include <iostream>
#include <sys/filio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "TestServer.h"
#include "SocketWindow.h"

TestServer::TestServer() {
    shouldExit = false;

    connections.resize(1);
    connections[0].fd = socket(AF_INET, SOCK_STREAM, 0);
    serverSocket = &connections[0].fd;
    connections[0].events = POLLIN;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SERVER_PORT);

    int on = 1;

    if (setsockopt(*serverSocket, SOL_SOCKET, SO_REUSEADDR,
                   (char *) &on, sizeof(on))) {
        std::cout << "setsockopt failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (ioctl(*serverSocket, FIONBIO, (char *) &on)) {
        std::cout << "Setting the socket to non-blocking failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (bind(*serverSocket, (struct sockaddr *) &address, sizeof(address)) < 0) {
        std::cout << "Binding socket failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    internalThread = std::thread(&TestServer::run, this);
}

void TestServer::run() {
    while (!shouldExit) {
        int pollReturn = poll(connections.data(), connections.size(), -1);
        if (pollReturn < 0) {
            std::cout << "Poll failed!" << std::endl;
            shouldExit = true;
            break;
        }
        if (pollReturn == 0) {
            std::cout << "Should not happen!" << std::endl;
            shouldExit = true;
            break;
        }

        //check for new connection requests
        if (connections[0].revents != POLLIN) {
            std::cout << "Error: revents = " << connections[0].revents << std::endl;
            shouldExit = true;
            break;
        }
        while (true) {
            int new_sd = accept(*serverSocket, NULL, NULL);
            if (new_sd < 0) {
                if (errno != EWOULDBLOCK) {
                    std::cout << "accept() failed" << std::endl;
                    shouldExit = true;
                    break;
                }
                break;
            }
            struct pollfd newConnection;
            newConnection.fd = new_sd;
            newConnection.events = POLL_IN;
            connections.emplace_back(newConnection);
        }

        //input from clients
        for (int i = 1; i < connections.size(); ++i) {
            bool closeConnection = false;
            char buffer[1024] = {0};

            while (true) {
                int rc = recv(connections[i].fd, buffer, sizeof(buffer), 0);
                if (rc < 0) {
                    if (errno != EWOULDBLOCK) {
                        perror("  recv() failed");
                        closeConnection = true;
                    }
                    break;
                }

                if (rc == 0) {
                    printf("  Connection closed\n");
                    closeConnection = true;
                    break;
                }

                printf("%d bytes received\n", rc);
                std::cout << buffer << std::endl;
            }

            if (closeConnection) {
                close(connections[i].fd);
                connections.erase(connections.begin() + i);
            }
        }
    }

    close(*serverSocket);
}

void TestServer::terminate() {
    shouldExit = true;
}

TestServer::~TestServer() {
    terminate();
    close(*serverSocket);
    internalThread.join();
}

int main(){
    TestServer server;
    std::cout << "Server running. To terminate press any key" << std::endl;
    char s;
    std::cin >> s;
    server.terminate();
    return 0;
}