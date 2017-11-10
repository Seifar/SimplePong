//
// Created by thomas on 10.11.17.
//

#include "PongLogic.h"

PongLogic::PongLogic(unsigned field_size, unsigned paddle_size) {
    this->field_size=field_size;
    this->paddle_size=paddle_size;
    current_direction=UPRIGHT;
}

PongLogic::~PongLogic() {

}
