//
// Created by Thomas Frank on 2019-01-31.
//

#include "Pong.h"
#include "cmath"

Pong::Pong() {
    fieldSize = {750, 500};

    paddleSize = fieldSize.second / 6;

    ballPos = {fieldSize.first / 2, fieldSize.second / 2};

    ballSpeedMultiplyer = 1;
    ballSpeed = {1,1};
    normalizeSpeed();

    positionP1 = positionP2 = fieldSize.second / 2;

}

Pong::~Pong() {

}

void Pong::normalizeSpeed() {
    double v = ballSpeedMultiplyer * sqrt( pow(ballSpeed.first, 2) + pow(ballSpeed.second, 2) );
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