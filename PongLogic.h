//
// Created by thomas on 10.11.17.
//

#ifndef PONG_PONGLOGIC_H
#define PONG_PONGLOGIC_H



class PongLogic {
public:
    //initializes the game
    PongLogic(unsigned field_size_x, unsigned field_size_y, unsigned paddle_size);
    ~PongLogic();

    enum direction{UPLEFT, UPRIGHT, DOWNRIGHT, DOWNLEFT};
    void startgame();

private:
    unsigned field_size, paddle_size;
    unsigned paddle_pos_left, paddle_pos_right;
    unsigned ball_Pos_x, ball_Pos_y;
    direction current_direction;
    unsigned points_left, points_right;

    void tick();
    void reset();

    //test if paddle can catch ball
    bool paddle_left_is(int y);
    bool paddle_right_is(int y);
};


#endif //PONG_PONGLOGIC_H
