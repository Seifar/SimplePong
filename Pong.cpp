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

    ballSpeedMultiplier = 5e-7;
    ballSpeed = {1, 1};
    normalizeSpeed();

    positionP1 = positionP2 = (fieldSize.second - paddleSize) / 2.; //half position

    directionP1 = directionP2 = 0;

    paddlespeed = 5e-7;

    lastTickRight = lastTickLeft = lastTickBall = std::chrono::high_resolution_clock::now();

}

Pong::~Pong() = default;

void Pong::normalizeSpeed() {
    double v = sqrt(pow(ballSpeed.first, 2) + pow(ballSpeed.second, 2));
    ballSpeed.first = ballSpeedMultiplier * ballSpeed.first / v;
    ballSpeed.second = ballSpeedMultiplier * ballSpeed.second / v;
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
    emptyQueue(eventQueueP1, lockQ1, positionP1, lastTickLeft, directionP1);
    emptyQueue(eventQueueP2, lockQ2, positionP2, lastTickRight, directionP2);

    //move ball
    auto now = std::chrono::high_resolution_clock::now();
    int duration = (int) (now - lastTickBall).count();

    double newBallPos;
    //x-axis movement
    newBallPos = ballPos.first + ballSpeed.first * duration;
    if (newBallPos - ballDiameter / 2. < 0) {
        // position during overlap

        if (ballPos.second > positionP1 && ballPos.second < positionP1 + paddleSize) {
            newBallPos = (newBallPos - ballDiameter / 2.) * -1 + ballDiameter / 2.;
            ballSpeed.first *= -1;
        } else {
            ballPos = {fieldSize.first / 2, fieldSize.second / 2};
            return;
        }
    } else if (newBallPos + ballDiameter / 2. > fieldSize.first) {
        //position during overlap
        if (ballPos.second > positionP2 && ballPos.second < positionP2 + paddleSize) {
            newBallPos -= 2 * (newBallPos + ballDiameter / 2. - fieldSize.first);
            ballSpeed.first *= -1;
        } else {
            ballPos = {fieldSize.first / 2, fieldSize.second / 2};
            return;
        }
    }
    ballPos.first = newBallPos;

    //y-axis movement
    newBallPos = ballPos.second + ballSpeed.second * duration;
    if (newBallPos - ballDiameter / 2. < 0) {
        newBallPos = (newBallPos - ballDiameter / 2.) * -1 + ballDiameter / 2.;
        ballSpeed.second *= -1;
    } else if (newBallPos + ballDiameter / 2. > fieldSize.second) {
        newBallPos -= 2 * (newBallPos + ballDiameter / 2. - fieldSize.second);
        ballSpeed.second *= -1;
    }
    ballPos.second = newBallPos;

    lastTickBall = now;
}

void
Pong::emptyQueue(std::queue<std::pair<event, std::chrono::time_point<std::chrono::high_resolution_clock>>> &eventQueue,
                 std::mutex &lock,
                 double &position, TimePoint &lastTick, int &direction) {
    lock.lock();
    bool updated = false;

    while (!eventQueue.empty()) {
        auto currentTick = std::chrono::high_resolution_clock::now();
        auto timeDistance = currentTick - lastTick;
        position -= paddlespeed * timeDistance.count() * direction;
        switch (eventQueue.front().first) {
            case upPressed:
                direction = 1;
                break;
            case downPressed:
                direction = -1;
                break;
            case upReleased:
            case downReleased:
                direction = 0;
                break;
        }

        position = std::max(position, 0.);
        position = std::min(position, fieldSize.second - paddleSize + .0);
        eventQueue.pop();
        lastTick = currentTick;
        updated = true;
    }

    if (!updated){
        auto currentTick = std::chrono::high_resolution_clock::now();
        auto timeDistance = currentTick - lastTick;
        position -= paddlespeed * timeDistance.count() * direction;
        position = std::max(position, 0.);
        position = std::min(position, fieldSize.second - paddleSize + .0);
        lastTick = currentTick;
    }
    lock.unlock();
}
