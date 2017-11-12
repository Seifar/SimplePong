#include <unistd.h>
#include "PongWindow.h"

int main() {

    PongWindow window(15, 3);
    while (1){
        char c =window.getchar();
        if(c==27){
            break;
        }
        sleep(.5);
    }
    window.getchar();
    return 0;
}