//
// Created by Thomas Frank on 2019-01-31.
//

#include "Pong.h"
#include "cmath"

#include <algorithm>
#include <iostream>

Pong::Pong() {
    fieldSize = {750, 500};

    paddleSize = fieldSize.second / 6;

    ballPos = {fieldSize.first / 2, fieldSize.second / 2};
    ballDiameter = 15;

    ballSpeedMultiplier = 1;
    ballSpeed = {1,1};
    normalizeSpeed();

    positionP1 = positionP2 = fieldSize.second / 2;

    directionP1 = directionP2 = 0;

    paddlespeed = 1;

}

Pong::~Pong() {

}

void Pong::normalizeSpeed() {
    double v = ballSpeedMultiplier * sqrt( pow(ballSpeed.first, 2) + pow(ballSpeed.second, 2) );
    ballSpeed.first /= v;
    ballSpeed.second /= v;
}

void Pong::upPressedPlayer1(){
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ1.lock();
    auto new_elem = std::pair<event , std::chrono::time_point<std::chrono::high_resolution_clock>>(upPressed, timePoint);
    eventQueueP1.push(new_elem);
    lockQ1.unlock();
}
void Pong::upReleasedPlayer1(){
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ1.lock();
    auto new_elem = std::pair<event , std::chrono::time_point<std::chrono::high_resolution_clock>>(upReleased, timePoint);
    eventQueueP1.push(new_elem);
    lockQ1.unlock();
}
void Pong::downPressedPlayer1(){
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ1.lock();
    auto new_elem = std::pair<event , std::chrono::time_point<std::chrono::high_resolution_clock>>(downPressed, timePoint);
    eventQueueP1.push(new_elem);
    lockQ1.unlock();
}
void Pong::downReleasedPlayer1(){
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ1.lock();
    auto new_elem = std::pair<event , std::chrono::time_point<std::chrono::high_resolution_clock>>(downReleased, timePoint);
    eventQueueP1.push(new_elem);
    lockQ1.unlock();
}
void Pong::upPressedPlayer2(){
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ2.lock();
    auto new_elem = std::pair<event , std::chrono::time_point<std::chrono::high_resolution_clock>>(upPressed, timePoint);
    eventQueueP1.push(new_elem);
    lockQ2.unlock();
}
void Pong::upReleasedPlayer2(){auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ2.lock();
    auto new_elem = std::pair<event , std::chrono::time_point<std::chrono::high_resolution_clock>>(upReleased, timePoint);
    eventQueueP1.push(new_elem);
    lockQ2.unlock();}
void Pong::downPressedPlayer2(){
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ2.lock();
    auto new_elem = std::pair<event , std::chrono::time_point<std::chrono::high_resolution_clock>>(downPressed, timePoint);
    eventQueueP1.push(new_elem);
    lockQ2.unlock();
}
void Pong::downReleasedPlayer2(){
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ2.lock();
    auto new_elem = std::pair<event , std::chrono::time_point<std::chrono::high_resolution_clock>>(downReleased, timePoint);
    eventQueueP1.push(new_elem);
    lockQ2.unlock();
    char** a;
}

void Pong::tick() {
    std::cout << "Player 1 Pos is " << positionP1 << std::endl;
    //empty input queues
    auto leftLast = lastTickLeft;
    lockQ1.lock();
    while (!eventQueueP1.empty())
    {
        switch (eventQueueP1.front().first){
            case upPressed:

                break;
            case upReleased:

                break;
            case downPressed:

                break;
            case downReleased:

                break;
        }

        positionP1 = std::max(0., positionP1);
        positionP1 = std::min((double) fieldSize.second, positionP2-paddleSize);
        leftLast = eventQueueP1.front().second;
        eventQueueP1.pop();
    }
    lockQ1.unlock();

    auto rightLast = lastTickRight;
    lockQ2.lock();
    while (!eventQueueP2.empty()){

    }
    lockQ2.unlock();

    sleep(1);
}
