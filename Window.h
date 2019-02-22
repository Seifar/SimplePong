//
// Created by Thomas Frank on 2019-02-07.
//

#ifndef PONG_WINDOW_H
#define PONG_WINDOW_H

#include <SFML/Graphics.hpp>
#include <thread>
#include "Pong.h"

class Window {
private:
    sf::RenderWindow window;
    Pong *modell;
    std::thread thread;

    double scalingFactor;
    std::pair<int, int> FieldOffset;

    void loop();
    void draw();
    void calculateStuff();

public:
    Window(Pong *modell);
    ~Window();
};


#endif //PONG_WINDOW_H
