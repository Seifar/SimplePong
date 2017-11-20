#include <unistd.h>
#include <iostream>
#include "PongWindow.h"

void test1(){
  std::cout << "Test1" << '\n';
}

void test2() {
  std::cout << "Test2" << '\n';
}

int main() {
    PongWindow window(15, 15, 3);
    /*while (1){
        char c =window.getchar();
        if(c==27){
            break;
        }
        sleep(.5);
    }
    window.getchar();*/
    return 0;
}
