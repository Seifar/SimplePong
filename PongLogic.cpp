//
// Created by thomas on 10.11.17.
//

#include "PongLogic.h"
#include <stdlib>
#include <time>
#include <stdio>

/*
*   PUBLIC
*/

PongLogic::PongLogic(unsigned field_size_x, unsigned field_size_y, unsigned paddle_size) {
    std::srand(std::time(0));
    this->field_size = field_size;
    this->paddle_size = paddle_size;
    current_direction = UPRIGHT;
    paddle_pos_left = 0;
    paddle_pos_right = 0;
    ball_Pos_x = field_size_x/2;
    ball_Pos_y = std::rand() % field_size_y;
    switch (std::rand()%4) {
      case 0:
        current_direction=UPLEFT;
        break;
      case 1:
        current_direction = UPRIGHT;
        break;
      case 2:
        current_direction = DOWNRIGHT;
        break;
      case 3:
        current_direction = DOWNLEFT;
        break;
      default:
        std::cout << "Pong Logic Constructor Error\n";
    }
}

PongLogic::~PongLogic() {

}

/*
*   PRIVATE
*/
//TODO better way: use function pointer instead of enum
void PongLogic::tick(){
    switch (current_direction) {
    case UPLEFT:
      if (ball_Pos_x == 1) {
        //test if paddle is in right place
        if (paddle_left_is(ball_Pos_y)) {
          if (ball_Pos_y == 0) {
            ball_Pos_x++;
            ball_Pos_y++;
            current_direction = DOWNRIGHT;
          }else{
            ball_Pos_x++;
            ball_Pos_y--;
            current_direction = UPRIGHT;
          }
        }else{
          //point for right side
          points_right++;
          reset;
        }
      }else{
        if(ball_Pos_y==0){
          ball_Pos_y++;
          ball_Pos_x--;
          current_direction = DOWNLEFT;
        }else{
          ball_Pos_x--;
          ball_Pos_y--;
        }
      }
      break;
    case UPRIGHT:
      break;
    case DOWNLEFT:
      break;
    case DOWNRIGHT:
      break;
      default:
       std::cout << "PongLogic Tick Error\n";
    }
}
