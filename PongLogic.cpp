//
// Created by thomas on 10.11.17.
//

#include "PongLogic.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <chrono>

using namespace std::chrono;

/*
*   PUBLIC
*/

PongLogic::PongLogic(unsigned field_size_x, unsigned field_size_y, unsigned paddle_size) {
    srand(time(0));
    this->field_size_x = field_size_x;
    this->field_size_y = field_size_y;
    this->paddle_size = paddle_size;
    paddle_pos_left = field_size_y/2-paddle_size/2;
    paddle_pos_right = field_size_y/2-paddle_size/2;
    input_buffer_left=0;
    input_buffer_right=0;
    reset();
}

PongLogic::~PongLogic() {

}

void PongLogic::startgame() {
    timer =  (long) std::chrono::high_resolution_clock::now().time_since_epoch().count();
    while (1) {
        long current_time = ((long) std::chrono::high_resolution_clock::now().time_since_epoch().count());
        if(current_time - timer > 1000000000/fps){
            //do tick
            timer = current_time;
            tick();
        }
    }
}


void PongLogic::add_view(PongView* view){
  views.push_back(view);
}

void PongLogic::move_paddle_left_up() {
  input_buffer_left--;
}

void PongLogic::move_paddle_left_down() {
  input_buffer_left++;
}

void PongLogic::move_paddle_right_up() {
  input_buffer_right--;
}

void PongLogic::move_paddle_right_down() {
  input_buffer_right++;
}

/*
*   PRIVATE
*/
void PongLogic::update_paddle_left() {
    int tmp_buf;

    //copy and empty input buffer
    input_buffer_lock.lock();
    tmp_buf = input_buffer_left;
    input_buffer_left = 0;
    input_buffer_lock.unlock();

    //update logic -- paddle is moved by input_buffer_left as far as possible
    if (paddle_pos_left + tmp_buf < 0) {
      paddle_pos_left = 0;
    }else if(paddle_pos_left + tmp_buf > field_size_y-1){
      paddle_pos_left = field_size_y-1;
    }else{
      paddle_pos_left = paddle_pos_left + tmp_buf;
    }
}

void PongLogic::update_paddle_right() {
    int tmp_buf;

    //copy and empty input buffer
    input_buffer_lock.lock();
    tmp_buf = input_buffer_right;
    input_buffer_right = 0;
    input_buffer_lock.unlock();

    //update logic -- paddle is moved by input_buffer_left as far as possible
    if (paddle_pos_right + tmp_buf < 0) {
      paddle_pos_right = 0;
    }else if(paddle_pos_right + tmp_buf > field_size_y-1){
      paddle_pos_right = field_size_y-1;
    }else{
      paddle_pos_right = paddle_pos_right + tmp_buf;
    }
}

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
          if (ball_Pos_y == field_size_y-1) {
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
        if(ball_Pos_y == field_size_y-1){
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
          if (ball_Pos_y == field_size_y-1) {
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
        if (ball_Pos_y == field_size_y-1) {
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

    update_views();
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
      std::cout << "Pong Logic Reset Error\n"; exit(-1);
  }
}

void PongLogic::update_views() {
  for (std::vector<int>::size_type i = 0; i < views.size(); i++) {
    views[i]->updateView(paddle_pos_left, paddle_pos_right, ball_Pos_x, ball_Pos_y);
  }
}

bool PongLogic::paddle_left_is(int y) {
  return y>=paddle_pos_left && y<=paddle_pos_left+paddle_size;
}

bool PongLogic::paddle_right_is(int y) {
  return y>=paddle_pos_right && y<=paddle_pos_right+paddle_size;
}
