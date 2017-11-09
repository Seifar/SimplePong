#include <curses.h>

const unsigned field_size = 15;
const unsigned paddle_size = 3;

void print_field(){
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
}

void print_ball(int x, int y){
    move(y+1, x*2+1);
    printw("[]");
}

void print_player(bool left, int height){
    int x=left?1:field_size;
    for (int i = 0; i < paddle_size; ++i) {
        move(height+i,x);
        printw("|");
    }

}

int main() {
    printf("%d\n",LINES);
    initscr();
    curs_set(0);

    print_field();
    print_ball(5,5);
    print_player(1,5);

    refresh();
    getch();
    endwin();

    return 0;
}