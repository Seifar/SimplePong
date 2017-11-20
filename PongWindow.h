//
// Created by thomas on 09.11.17.
//

#ifndef PONG_PONGWINDOW_H
#define PONG_PONGWINDOW_H


class PongWindow : public PongView{
public:
    PongWindow(unsigned field_size_x, unsigned field_size_y, unsigned paddle_size)
    : PongView(field_size_x, field_size_y, paddle_size);
    ~PongWindow() : ~PongView();
    updateView(int left_paddle_pos, int right_paddle_pos,
      virtual int ball_Pos_x, int ball_Pos_y) = 0; //-1 in argument doesnt update View

private:


    void print_field();
    void print_ball(int x, int y);
    void print_player(bool left, int height);
    char getchar();
};


#endif //PONG_PONGWINDOW_H
