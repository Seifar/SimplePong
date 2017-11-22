//
// Created by thomas on 09.11.17.
//
#include "PongView.h"

#ifndef PONG_PONGWINDOW_H
#define PONG_PONGWINDOW_H


class PongWindow : public PongView{
public:
    PongWindow(unsigned field_size_x, unsigned field_size_y, unsigned paddle_size);
    ~PongWindow();
    void updateView(int left_paddle_pos, int right_paddle_pos,
      int ball_Pos_x, int ball_Pos_y); //-1 in argument doesnt update View

private:
    void print_field();
    void print_ball(int x, int y);
    void print_player(bool left, int height);
    char getchar();
};


#endif //PONG_PONGWINDOW_H
