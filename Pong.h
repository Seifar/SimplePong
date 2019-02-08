//
// Created by Thomas Frank on 2019-01-31.
//

#ifndef PONG_PONGCONTROL_H
#define PONG_PONGCONTROL_H


#include <utility>
#include <queue>
#include <chrono>
#include <mutex>

class PongControl {
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
    double ballSpeedMultiplyer;
    double positionP1, positionP2;

    // input queues
    std::queue<std::pair<event , std::chrono::time_point<std::chrono::high_resolution_clock>>> eventQueueP1, eventQueueP2;
    std::mutex lockQ1, lockQ2;

    //methods
    void normalizeSpeed();

public:
    PongControl();
    ~PongControl();

    void upPressedPlayer1();
    void upReleasedPlayer1();
    void downPressedPlayer1();
    void downReleasedPlayer1();
    void upPressedPlayer2();
    void upReleasedPlayer2();
    void downPressedPlayer2();
    void downReleasedPlayer2();
};


#endif //PONG_PONGCONTROL_H
