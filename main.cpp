#include <unistd.h>
#include <iostream>
#include <thread>

#include "Pong.h"
#include "Window.h"

int main(int argc, const char * argv[]) {
    Pong *game = new Pong();
    std::thread t([game](){game->loop();});
    Window window(game);

    game->terminate();
    t.join();
    return 0;
}
