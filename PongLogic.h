//
// Created by thomas on 10.11.17.
//
#include <vector>
#include <mutex>
#include <thread>

#include "PongView.h"

#ifndef PONG_PONGLOGIC_H
#define PONG_PONGLOGIC_H


class PongLogic {
public:
    double fps = 5.0;

    //initializes the game
    PongLogic(unsigned field_size_x, unsigned field_size_y, unsigned paddle_size);
    ~PongLogic();

    enum direction{UPLEFT, UPRIGHT, DOWNRIGHT, DOWNLEFT};
    void start_game();

    //add views which should get updated
    void add_view(PongView* view);

private:
    long timer;

    unsigned field_size_x, field_size_y, paddle_size;
    int paddle_pos_left, paddle_pos_right;
    unsigned ball_Pos_x, ball_Pos_y;
    direction current_direction;
    unsigned points_left, points_right;

    std::vector<PongView*> views;
    int input_buffer_left;
    int input_buffer_right;
    std::thread* t; //thread running PongLogic

    //update paddle positions according to buffer
    std::mutex input_buffer_lock;
    void update_paddle_left();
    void update_paddle_right();

    void tick(); // each tick the ball moves by 1 and the paddle positions get updated
    void reset();
    void update_views();

    //test if paddle can catch ball
    bool paddle_left_is(int y);
    bool paddle_right_is(int y);
};


#endif //PONG_PONGLOGIC_H
