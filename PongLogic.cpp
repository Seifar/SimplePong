//
// Created by thomas on 10.11.17.
//

#include "PongLogic.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

/*
*   PUBLIC
*/

PongLogic::PongLogic(unsigned field_size_x, unsigned field_size_y, unsigned paddle_size) {
    srand(time(0));
    this->field_size_x = field_size_x;
    this->field_size_y = field_size_y;
    this->paddle_size = paddle_size;
    paddle_pos_left = 0;
    paddle_pos_right = 0;
    reset();
}

PongLogic::~PongLogic() {

}

void move_paddle_left_up() {
  if (paddle_pos_left > 0) {
    paddle_pos_left--;
  }
}

void move_paddle_left_down() {
  if (field_size_y > paddle_pos_left+paddle_size) {
    paddle_pos_left++;
  }
}

void move_paddle_right_up(/* arguments */) {
  if (paddle_pos_right>0) {
    paddle_pos_right--;
  }
}

void move_paddle_right_down() {
  if(field_size_y > paddle_pos_right+paddle_size){
    paddle_pos_right++;
  }
}

/*
*   PRIVATE
*/
void PongLogic::tick(){
    switch (current_direction) {
    case UPLEFT:
      if (ball_Pos_x == 1) {
        //test if paddle is in right place
        if (paddle_left_is(ball_Pos_y)) {
          if (ball_Pos_y == 0) {
            ball_Pos_x++;  ball_Pos_y++;
            current_direction = DOWNRIGHT;
          }else{
            ball_Pos_x++;  ball_Pos_y--;
            current_direction = UPRIGHT;
          }
        }else{
          //point for right side
          points_right++;
          reset();
        }
      }else{
        if(ball_Pos_y==0){
          ball_Pos_x--;  ball_Pos_y++;
          current_direction = DOWNLEFT;
        }else{
          ball_Pos_x--;  ball_Pos_y--;
        }
      }
      break;

    case UPRIGHT:
      if (ball_Pos_x == field_size_x-2) {
        //test if paddle is in right place
        if (paddle_right_is(ball_Pos_y)) {
          if (ball_Pos_y == 0) {
            ball_Pos_x--;  ball_Pos_y++;
            current_direction = DOWNLEFT;
          } else {
            ball_Pos_x--;  ball_Pos_y--;
            current_direction = UPLEFT;
          }
        } else { //paddle right is not
          points_left++;
          reset();
        }
      } else { //ball is not next to paddle
        if (ball_Pos_y == 0) {
          ball_Pos_x++;  ball_Pos_y++;
          current_direction = DOWNRIGHT;
        } else {
          ball_Pos_x++;  ball_Pos_y--;
        }
      }
      break;

    case DOWNLEFT:
      if (ball_Pos_x == 1) {
        //test if paddle is in right place
        if (paddle_left_is(ball_Pos_y)) {
          if (ball_Pos_y == 0) {
            ball_Pos_x++;  ball_Pos_y--;
            current_direction = UPRIGHT;
          }else{
            ball_Pos_x++;  ball_Pos_y++;
            current_direction = DOWNRIGHT;
          }
        }else{
          //point for right side
          points_right++;
          reset();
        }
      }else{
        if(ball_Pos_y == field_size_y-2){
          ball_Pos_x--;  ball_Pos_y--;
          current_direction = UPLEFT;
        }else{
          ball_Pos_x--;  ball_Pos_y++;
        }
      }
      break;

    case DOWNRIGHT:
      if (ball_Pos_x == field_size_x-2) {
        //test if paddle is in right place
        if (paddle_right_is(ball_Pos_y)) {
          if (ball_Pos_y == 0) {
            ball_Pos_x--;  ball_Pos_y--;
            current_direction = UPLEFT;
          } else {
            ball_Pos_x--;  ball_Pos_y++;
            current_direction = DOWNLEFT;
          }
        } else { //paddle right is not
          points_left++;
          reset();
        }
      } else { //ball is not next to paddle
        if (ball_Pos_y == field_size_y-2) {
          ball_Pos_x++;  ball_Pos_y--;
          current_direction = UPRIGHT;
        } else {
          ball_Pos_x++;  ball_Pos_y++;
        }
      }
      break;

      default:
       std::cout << "PongLogic Tick Error\n";
    }
}

void PongLogic::reset() {
  ball_Pos_x = field_size_x/2;
  ball_Pos_y = rand() % field_size_y;
  switch (rand()%4) {
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
      std::cout << "Pong Logic Reset Error\n";
  }
}

bool PongLogic::paddle_left_is(int y) {
  return y>=paddle_pos_left && y<=paddle_pos_left+paddle_size;
}

bool PongLogic::paddle_right_is(int y) {
  return y>=paddle_pos_right && y<=paddle_pos_right+paddle_size;
}
