//
// Created by thomas on 09.11.17.
//
#include <ncurses.h>
#include <stdlib.h>
#include "PongWindow.h"
#include "PongView.h"

 PongWindow::PongWindow(unsigned field_size_x, unsigned field_size_y, unsigned paddle_size)
 : PongView(field_size_x, field_size_y, paddle_size){
     initscr();
     nodelay(stdscr,true);
     noecho();
     scrollok(stdscr,true);
     curs_set(0);
     print_field();
 }

 void PongWindow::updateView(int left_paddle_pos, int right_paddle_pos,
   int ball_Pos_x, int ball_Pos_y){ //-1 in argument doesnt update View
     if(left_paddle_pos >= 0)
      print_player(1, left_paddle_pos);
     if(right_paddle_pos >=0)
      print_player(2, right_paddle_pos);
    if(ball_Pos_x >= 0 && ball_Pos_y >=0)
      print_ball(ball_Pos_x, ball_Pos_y);
   }

 void PongWindow::print_field(){
    move(0,0);
    for (int i = 0; i < field_size_x+2; ++i) {
        printw("# ");
    }
    for (int i = 1; i <= field_size_y; ++i) {
        move(i,0);
        printw("#");
        move(i,(field_size_x*2)+3);
        printw("#");
    }
    move(field_size_y+1,0);
    for (int i = 0; i < field_size_y+2; ++i) {
        printw(" #");
    }
     refresh();
 }

 void PongWindow::print_ball(int x, int y){
    //clear screen
    for (unsigned y = 1; y < field_size_y-2; y++) {
      move(y, 2);
      for (unsigned x = 2; x < field_size_x-3; x++) {
        printw("  ");
      }
    }
    //print ball
    move(y+1, x*2+1);
    printw("[]");
     refresh();
 }

 void PongWindow::print_player(bool left, int height){
    int x=left?1:field_size_x-2;
    for (int i = 0; i < field_size_y; ++i) {
        move(i,x);
        if(i < height || i > height ) {
          if(inch()!='|'){
            printw("|");
          }
        } else {
          if (inch()!=' ') {
            printw(" ");
          }
        }
    }
    refresh();
 }

PongWindow::~PongWindow(){
    endwin();
}

char PongWindow::getchar() {
    char ch = getch();
    if(ch != ERR){
        return ch;
    }else{
        return -1;
    }
}
