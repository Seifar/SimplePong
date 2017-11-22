#include <unistd.h>
#include <iostream>
#include "PongWindow.h"
#include "PongLogic.h"
#include "PongController.h"

const unsigned field_size_x=20, field_size_y=15, paddle_size=3;

int main() {
    PongLogic logic(field_size_x, field_size_y, paddle_size);
    PongView *window = new PongWindow(field_size_x, field_size_y, paddle_size);
    logic.add_view(window);
    logic.startgame();
    /*PongController left;
    PongController right;*/
    while (1) {
      /* just keep window open */
    }
    return 0;
}
