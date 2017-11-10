//
// Created by thomas on 09.11.17.
//

#ifndef PONG_PONG_H
#define PONG_PONG_H


class PongWindow {
private:
    unsigned field_size;
    unsigned paddle_size;
public:
    PongWindow(unsigned field_size, unsigned paddle_size);
    ~PongWindow();
    void print_field();
    void print_ball(int x, int y);
    void print_player(bool left, int height);
    char getchar();
};


#endif //PONG_PONG_H
