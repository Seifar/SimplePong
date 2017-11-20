
#ifndef PONG_PONGVIEW_H
#define PONG_PONGVIEW_H

class PongView{

public:
  virtual PongWindow(unsigned field_size_x, unsigned field_size_y, unsigned paddle_size){
    this->field_size_x = field_size_x;
    this->field_size_y = field_size_y;
    this->paddle_size = paddle_size;
  }
  virtual ~PongWindow();
  virtual updateView(int left_paddle_pos, int right_paddle_pos,
    int ball_Pos_x, int ball_Pos_y) = 0; //-1 in argument doesnt update View

private:
      virtual unsigned field_size_x, field_size_y;
      virtual unsigned paddle_size;
};

#endif //PONG_PONGVIEW_H
