//
// Created by thomas on 09.11.17.
//
#include <ncurses.h>
#include <stdlib.h>
#include <string>
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
     print_player(true, 5);
     refresh();
 }

PongWindow::~PongWindow(){
    endwin();
}

 void PongWindow::updateView(int left_paddle_pos, int right_paddle_pos,
   int ball_Pos_x, int ball_Pos_y){ //-1 in argument doesnt update View
     if(left_paddle_pos >= 0)
      print_player(1, left_paddle_pos);
     if(right_paddle_pos >=0)
      print_player(0, right_paddle_pos);
    if(ball_Pos_x >= 0 && ball_Pos_y >=0)
      print_ball(ball_Pos_x, ball_Pos_y);

    refresh();
   }

 void PongWindow::print_field(){
    move(0,0);
    for (int i = 0; i < field_size_x+1; ++i) {
        printw("# ");
    }
    for (int i = 1; i <= field_size_y; ++i) {
        move(i,0);
        printw("#");
        move(i,(field_size_x*2)+1);
        printw("#");
    }
    move(field_size_y+1,0);
    for (int i = 0; i < field_size_x+1; ++i) {
        printw(" #");
    }
     refresh();
 }

 void PongWindow::print_ball(int x, int y){
    //clear screen
    for (unsigned y = 0; y < field_size_y; y++) {
      move(y+1, 3);
      //ignore space for paddles
      for (unsigned x = 1; x < field_size_x-1; x++) {
        printw("  ");
      }
    }
    //print ball
    move(y+1, x*2+1);
    printw("[]");
     refresh();
 }

 void PongWindow::print_player(bool left, int height){
    //TODO
    int x=left?1:1+(field_size_x*2)-2;
    for (int i = 0; i < field_size_y; i++) {
        move(i+1,x);
        if(i >= height && i < height+paddle_size ) {
          printw("||");
        } else {
          printw("  ");
        }
    }
    refresh();
 }

char PongWindow::getchar() {
    char ch = getch();
    if(ch != ERR){
        return ch;
    }else{
        return -1;
    }
}
