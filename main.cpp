#include <unistd.h>
#include <iostream>
#include <thread>

#include "Pong.h"
#include "Window.h"
#include "TestServer.h"
#include "SocketWindow.h"

int main(int argc, const char *argv[]) {
    Pong *game = new Pong();
    std::thread gameThread(&Pong::loop, game);

    SocketWindow socketWindow(game);
    std::thread sendThread(&SocketWindow::sendLoop, socketWindow);

    Window window(game);

    socketWindow.stop();
    game->terminate();

    sendThread.join();
    gameThread.join();
    return 0;
}
