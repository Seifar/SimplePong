//
// Created by Thomas Frank on 2019-01-31.
//

#include "PongControl.h"

#include "cmath"

PongControl::PongControl() {
    fieldSize = {750, 500};

    paddleSize = fieldSize.second / 6;

    ballPos = {fieldSize.first / 2, fieldSize.second / 2};

    ballSpeedMultiplyer = 1;
    ballSpeed = {1,1};
    normalizeSpeed();

    positionP1 = positionP2 = fieldSize.second / 2;

}

PongControl::~PongControl() {

}

void PongControl::normalizeSpeed() {
    double v = ballSpeedMultiplyer * sqrt( pow(ballSpeed.first, 2) + pow(ballSpeed.second, 2) );
    ballSpeed.first /= v;
    ballSpeed.second /= v;
}

void PongControl::upPressedPlayer1(){
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ1.lock();
    auto new_elem = std::pair<event , std::chrono::time_point<std::chrono::high_resolution_clock>>(upPressed, timePoint);
    eventQueueP1.push(new_elem);
    lockQ1.unlock();
}
void PongControl::upReleasedPlayer1(){
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ1.lock();
    auto new_elem = std::pair<event , std::chrono::time_point<std::chrono::high_resolution_clock>>(upReleased, timePoint);
    eventQueueP1.push(new_elem);
    lockQ1.unlock();
}
void PongControl::downPressedPlayer1(){
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ1.lock();
    auto new_elem = std::pair<event , std::chrono::time_point<std::chrono::high_resolution_clock>>(downPressed, timePoint);
    eventQueueP1.push(new_elem);
    lockQ1.unlock();
}
void PongControl::downReleasedPlayer1(){
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ1.lock();
    auto new_elem = std::pair<event , std::chrono::time_point<std::chrono::high_resolution_clock>>(downReleased, timePoint);
    eventQueueP1.push(new_elem);
    lockQ1.unlock();
}
void PongControl::upPressedPlayer2(){
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ2.lock();
    auto new_elem = std::pair<event , std::chrono::time_point<std::chrono::high_resolution_clock>>(upPressed, timePoint);
    eventQueueP1.push(new_elem);
    lockQ2.unlock();
}
void PongControl::upReleasedPlayer2(){auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ2.lock();
    auto new_elem = std::pair<event , std::chrono::time_point<std::chrono::high_resolution_clock>>(upReleased, timePoint);
    eventQueueP1.push(new_elem);
    lockQ2.unlock();}
void PongControl::downPressedPlayer2(){
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ2.lock();
    auto new_elem = std::pair<event , std::chrono::time_point<std::chrono::high_resolution_clock>>(downPressed, timePoint);
    eventQueueP1.push(new_elem);
    lockQ2.unlock();
}
void PongControl::downReleasedPlayer2(){
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ2.lock();
    auto new_elem = std::pair<event , std::chrono::time_point<std::chrono::high_resolution_clock>>(downReleased, timePoint);
    eventQueueP1.push(new_elem);
    lockQ2.unlock();
}