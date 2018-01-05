//
// Created by thomas on 09.11.17.
//
#include <mutex>
#include <thread>
#include "PongView.h"

#ifndef PONG_PONGWINDOW_H
#define PONG_PONGWINDOW_H


class PongWindow : public PongView{
public:
    PongWindow(unsigned field_size_x, unsigned field_size_y, unsigned paddle_size);
    ~PongWindow();
    void updateView(int left_paddle_pos, int right_paddle_pos,
      int ball_Pos_x, int ball_Pos_y, int score_left, int score_right) override; //-1 in argument doesnt update View
    int get_height_update_r() override;
    int get_height_update_l() override;
private:
    void print_field();
    void print_ball(int x, int y);
    void print_player(bool left, int height);
    void print_points(int l, int r);
    static  void* get_input();
/*
 * read input in queue
 */

    static std::mutex right_input_lock;
    static std::mutex left_input_lock;
    static int left_input; //ws
    static int right_input; //ol
    std::thread * thread;
};


#endif //PONG_PONGWINDOW_H
