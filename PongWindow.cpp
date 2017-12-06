//
// Created by thomas on 09.11.17.
//
#include <ncurses.h>
#include <stdlib.h>
#include <string>
#include "PongWindow.h"

int PongWindow::left_input=0;
int PongWindow::right_input=0;
std::mutex  PongWindow::left_input_lock;
std::mutex PongWindow::right_input_lock;

 PongWindow::PongWindow(unsigned field_size_x, unsigned field_size_y, unsigned paddle_size)
 : PongView(field_size_x, field_size_y, paddle_size){
     initscr();
     noecho();
     scrollok(stdscr,true);
     curs_set(0);
     print_field();
     left_input=0;
     right_input=0;
     thread = new std::thread(PongWindow::get_input);
     refresh();
 }

PongWindow::~PongWindow(){
    endwin();
}

 void PongWindow::updateView(int left_paddle_pos, int right_paddle_pos,
   int ball_Pos_x, int ball_Pos_y, int score_left, int score_right){ //-1 in argument doesnt update View
     if(left_paddle_pos >= 0)
      print_player(1, left_paddle_pos);
     if(right_paddle_pos >=0)
      print_player(0, right_paddle_pos);
    if(ball_Pos_x >= 0 && ball_Pos_y >=0)
      print_ball(ball_Pos_x, ball_Pos_y);
    if(score_left>=0 && score_right>=0){
        print_points(score_left,score_right);
    }
    refresh();
   }

 void PongWindow::print_field(){
    move(1,0);
    for (int i = 0; i < field_size_x+1; ++i) {
        printw("# ");
    }
    for (int i = 1; i <= field_size_y; ++i) {
        move(i+1,0);
        printw("#");
        move(i+1,(field_size_x*2)+1);
        printw("#");
    }
    move(field_size_y+2,0);
    for (int i = 0; i < field_size_x+1; ++i) {
        printw(" #");
    }
     refresh();
 }

 void PongWindow::print_ball(int x, int y){
    //clear screen
    for (unsigned y = 0; y < field_size_y; y++) {
      move(y+2, 3);
      //ignore space for paddles
      for (unsigned x = 1; x < field_size_x-1; x++) {
        printw("  ");
      }
    }
    //print ball
    move(y+2, x*2+1);
    printw("[]");
     refresh();
 }

 void PongWindow::print_player(bool left, int height){
    //TODO
    int x=left?1:1+(field_size_x*2)-2;
    for (int i = 0; i < field_size_y; i++) {
        move(i+2,x);
        if(i >= height && i < height+paddle_size ) {
          printw("||");
        } else {
          printw("  ");
        }
    }
    refresh();
 }



void  * PongWindow::get_input() {
    while (1){
        char ch = getch();
        switch (ch){
            case 'w':
                (left_input_lock).lock();
                left_input--;
                (left_input_lock).unlock();
                break;
            case 's':
                (left_input_lock).lock();
                left_input++;
                (left_input_lock).unlock();
                break;
            case 'o':
                (right_input_lock).lock();
                right_input--;
                (right_input_lock).unlock();
                break;
            case 'l':
                (right_input_lock).lock();
                right_input++;
                (right_input_lock).unlock();
                break;
            default:
                break;
        }
    }
}

int PongWindow::get_height_update_l() {
    (left_input_lock).lock();
    int ret = left_input;
    left_input=0;
    (left_input_lock).unlock();
    return ret;
}

int PongWindow::get_height_update_r() {
    (right_input_lock).lock();
    int ret = right_input;
    right_input=0;
    (right_input_lock).unlock();
    return ret;
}

void PongWindow::print_points(int l, int r) {
    move(0,0);
    printw("Left: %d", l);
    move(0,10);
    printw("Right: %d",r);
}
