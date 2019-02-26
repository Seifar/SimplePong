//
// Created by Thomas Frank on 2019-02-07.
//

#include <unistd.h>
#include <iostream>

#include "Window.h"

Window::Window(Pong *modell) {
    this->modell = modell;

    //create window
    window.create(sf::VideoMode(800, 600), "Pong");
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(60);

    //draw field and start loop
    calculateStuff();
    draw();
    loop();
}

Window::~Window() = default;

void Window::loop() {

    //handle events from window
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.waitEvent(event)) {
            switch (event.type) {
                case sf::Event::KeyPressed:
                    // enque event in Pong physics
                    switch (event.key.code) {
                        case sf::Keyboard::W:
                            modell->upPressedPlayer1();
                            break;
                        case sf::Keyboard::S:
                            modell->downPressedPlayer1();
                            break;
                        case sf::Keyboard::Up:
                            modell->upPressedPlayer2();
                            break;
                        case sf::Keyboard::Down:
                            modell->downPressedPlayer2();
                            break;
                        default:
                            break;
                    }
                    break;

                case sf::Event::KeyReleased:
                    // enque event in Pong physics
                    switch (event.key.code) {
                        case sf::Keyboard::W:
                            modell->upReleasedPlayer1();
                            break;
                        case sf::Keyboard::S:
                            modell->downReleasedPlayer1();
                            break;
                        case sf::Keyboard::Up:
                            modell->upReleasedPlayer2();
                            break;
                        case sf::Keyboard::Down:
                            modell->downReleasedPlayer2();
                            break;
                        default:
                            break;
                    }
                    break;

                case sf::Event::Closed:
                    //close request
                    window.close();
                    break;
                case sf::Event::Resized:
                    window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                    calculateStuff();
                    draw();
                    break;
                default:
                    break;
            }

            draw();
        }
    }
}

void Window::draw() {
    static bool foo = false;
    //clear canvas
    window.clear(sf::Color(50, 50, 50));

    //create all shapes
    sf::RectangleShape field(
            sf::Vector2f(modell->getSize().first * scalingFactor, modell->getSize().second * scalingFactor));
    field.setFillColor(sf::Color::Black);
    field.setPosition(FieldOffset.first, FieldOffset.second);

    sf::RectangleShape paddleLeft(sf::Vector2f(0, modell->getPaddleSize() * scalingFactor));
    paddleLeft.setFillColor(sf::Color::White);
    paddleLeft.setPosition(FieldOffset.first, FieldOffset.second + scalingFactor * modell->getPositionP1());
    paddleLeft.setOutlineThickness(5 * scalingFactor);

    sf::RectangleShape paddleRight(sf::Vector2f(0, modell->getPaddleSize() * scalingFactor));
    paddleRight.setFillColor(sf::Color::White);
    paddleRight.setPosition(FieldOffset.first + field.getSize().x,
                            FieldOffset.second + scalingFactor * modell->getPositionP2());
    paddleRight.setOutlineThickness(5 * scalingFactor);

    sf::CircleShape ball(modell->getBallDiameter() * scalingFactor / 2);
    ball.setOrigin(ball.getRadius(), ball.getRadius());
    ball.setFillColor(sf::Color::Yellow);
    ball.setPosition(FieldOffset.first + modell->getBallPos().first * scalingFactor,
                     FieldOffset.second + modell->getBallPos().second * scalingFactor);


    //draw all shapes
    window.draw(field);
    window.draw(ball);
    window.draw(paddleLeft);
    window.draw(paddleRight);

    //display new image
    window.display();

    foo = !foo;
}

void Window::calculateStuff() {
    double scalingX = (double) window.getSize().x / modell->getSize().first;
    double scalingY = (double) window.getSize().y / modell->getSize().second;

    if (scalingX < scalingY) {
        //will be fitted to width
        scalingFactor = scalingX;
        FieldOffset = std::pair<int, int>(0, (window.getSize().y - modell->getSize().second * scalingFactor) / 2);
    } else {
        //will be fitted to height
        scalingFactor = scalingY;
        FieldOffset = std::pair<int, int>((window.getSize().x - modell->getSize().first * scalingFactor) / 2, 0);
    }
}
