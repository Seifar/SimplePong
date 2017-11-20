//
// Created by thomas on 09.11.17.
//
#include <ncurses.h>
#include <stdlib.h>
#include "PongWindow.h"

 PongWindow::PongWindow(unsigned field_size, unsigned paddle_size)
 : PongView(field_size_x, field_size_y, paddle_size){
     initscr();
     nodelay(stdscr,true);
     noecho();
     scrollok(stdscr,true);
     curs_set(0);
     print_field();
 }
 void PongWindow::print_field(){
    move(0,0);
    for (int i = 0; i < field_size+2; ++i) {
        printw("# ");
    }
    for (int i = 1; i <= field_size; ++i) {
        move(i,0);
        printw("#");
        move(i,(field_size*2)+3);
        printw("#");
    }
    move(field_size+1,0);
    for (int i = 0; i < field_size+2; ++i) {
        printw(" #");
    }
     refresh();
 }

 void PongWindow::print_ball(int x, int y){
    move(y+1, x*2+1);
    printw("[]");
     refresh();
 }

 void PongWindow::print_player(bool left){
    int x=left?1:field_size;
    for (int i = 0; i < field_size_y; ++i) {
        move(i,x);
        if(i < left?paddle_pos_left:paddle_pos_right || i > (left?paddle_pos_left:paddle_pos_right)+paddle_size ) {
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

PongWindow::~PongWindow() {
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
