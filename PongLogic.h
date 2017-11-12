//
// Created by thomas on 10.11.17.
//

#ifndef PONG_PONGLOGIC_H
#define PONG_PONGLOGIC_H



class PongLogic {
public:
    PongLogic(unsigned field_size, unsigned paddle_size);
    ~PongLogic();
    enum direction{UPLEFT, UPRIGHT, DOWNRIGHT, DOWNLEFT};

private:
    unsigned field_size, paddle_size;
    unsigned x, y;
    direction current_direction;
};


#endif //PONG_PONGLOGIC_H
