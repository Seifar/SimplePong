//
// Created by Thomas Frank on 2019-01-31.
//

#ifndef PONG_PONGCONTROL_H
#define PONG_PONGCONTROL_H


#include <utility>
#include <queue>
#include <chrono>
#include <mutex>

#include <unistd.h>
#include <iostream>
#include <thread>

class Pong {
private:
    enum event{
        upPressed,
        upReleased,
        downPressed,
        downReleased
    };

    // game state
    std::pair<int, int> fieldSize;
    int paddleSize, ballDiameter;
    std::pair<double, double> ballPos, ballSpeed;
    double ballSpeedMultiplier;
    double positionP1, positionP2;
    int directionP1, directionP2;
    double paddlespeed; // ϵ {-1, 0, 1}

    bool terminated = false;


    // input queues
    std::queue<std::pair<event , std::chrono::time_point<std::chrono::high_resolution_clock>>> eventQueueP1, eventQueueP2;
    std::mutex lockQ1, lockQ2;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTickLeft, lastTickRight;

    //methods
    void normalizeSpeed();

public:
    Pong();
    ~Pong();

    void tick();
    void loop(){while (!terminated) tick();}
    void terminate(){terminated = true;}

    void upPressedPlayer1();
    void upReleasedPlayer1();
    void downPressedPlayer1();
    void downReleasedPlayer1();
    void upPressedPlayer2();
    void upReleasedPlayer2();
    void downPressedPlayer2();
    void downReleasedPlayer2();

    //getters
    std::pair<int, int> getSize() {return fieldSize;};
    int getPaddleSize() {return paddleSize;}
    int getBallDiameter() { return ballDiameter;};
    std::pair<double, double> getBallPos() {return ballPos;};
    double getPositionP1() {return positionP1;};
    double getPositionP2() { return  positionP2;};

};


#endif //PONG_PONGCONTROL_H
