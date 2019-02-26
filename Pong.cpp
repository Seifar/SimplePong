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

    ballSpeedMultiplier = 1./100;
    ballSpeed = {1, 1};
    normalizeSpeed();

    positionP1 = positionP2 = (fieldSize.second - paddleSize)  / 1.; //half position

    directionP1 = directionP2 = 0;

    paddlespeed = 1;

    lastTickRight = lastTickLeft = lastTickLeft = std::chrono::high_resolution_clock::now();

}

Pong::~Pong() = default;

void Pong::normalizeSpeed() {
    double v = ballSpeedMultiplier * sqrt(pow(ballSpeed.first, 2) + pow(ballSpeed.second, 2));
    ballSpeed.first /= v;
    ballSpeed.second /= v;
}

void Pong::upPressedPlayer1() {
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ1.lock();
    auto new_elem = std::pair<event, std::chrono::time_point<std::chrono::high_resolution_clock>>(upPressed, timePoint);
    eventQueueP1.push(new_elem);
    lockQ1.unlock();
}

void Pong::upReleasedPlayer1() {
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ1.lock();
    auto new_elem = std::pair<event, std::chrono::time_point<std::chrono::high_resolution_clock>>(upReleased,
                                                                                                  timePoint);
    eventQueueP1.push(new_elem);
    lockQ1.unlock();
}

void Pong::downPressedPlayer1() {
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ1.lock();
    auto new_elem = std::pair<event, std::chrono::time_point<std::chrono::high_resolution_clock>>(downPressed,
                                                                                                  timePoint);
    eventQueueP1.push(new_elem);
    lockQ1.unlock();
}

void Pong::downReleasedPlayer1() {
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ1.lock();
    auto new_elem = std::pair<event, std::chrono::time_point<std::chrono::high_resolution_clock>>(downReleased,
                                                                                                  timePoint);
    eventQueueP1.push(new_elem);
    lockQ1.unlock();
}

void Pong::upPressedPlayer2() {
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ2.lock();
    auto new_elem = std::pair<event, std::chrono::time_point<std::chrono::high_resolution_clock>>(upPressed, timePoint);
    eventQueueP2.push(new_elem);
    lockQ2.unlock();
}

void Pong::upReleasedPlayer2() {
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ2.lock();
    auto new_elem = std::pair<event, std::chrono::time_point<std::chrono::high_resolution_clock>>(upReleased,
                                                                                                  timePoint);
    eventQueueP2.push(new_elem);
    lockQ2.unlock();
}

void Pong::downPressedPlayer2() {
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ2.lock();
    auto new_elem = std::pair<event, std::chrono::time_point<std::chrono::high_resolution_clock>>(downPressed,
                                                                                                  timePoint);
    eventQueueP2.push(new_elem);
    lockQ2.unlock();
}

void Pong::downReleasedPlayer2() {
    auto timePoint = std::chrono::high_resolution_clock::now();
    lockQ2.lock();
    auto new_elem = std::pair<event, std::chrono::time_point<std::chrono::high_resolution_clock>>(downReleased,
                                                                                                  timePoint);
    eventQueueP2.push(new_elem);
    lockQ2.unlock();
    char **a;
}

void Pong::tick() {
    emptyQueue(eventQueueP1, lockQ1, positionP1, lastTickLeft);
    emptyQueue(eventQueueP2, lockQ2, positionP2, lastTickRight);

    //move ball
    auto now = std::chrono::high_resolution_clock::now();

    int duration = (int) (now - lastTickBall).count();


    lastTickBall = now;
}

void
Pong::emptyQueue(std::queue<std::pair<event, std::chrono::time_point<std::chrono::high_resolution_clock>>> &eventQueue,
                 std::mutex &lock,
                 double &position, std::chrono::time_point<std::chrono::high_resolution_clock> &lastTick) {
    auto leftLast = lastTick;
    lock.lock();
    while (!eventQueue.empty()) {
        switch (eventQueue.front().first) {
            case upPressed:
                position -= 10;
                break;
            case upReleased:

                break;
            case downPressed:
                position += 10;
                break;
            case downReleased:

                break;
        }

        position = std::max(position, 0.);
        position = std::min(position, fieldSize.second - paddleSize + .0);
        eventQueue.pop();
    }
    lock.unlock();
}
