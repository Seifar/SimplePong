
#ifndef PONG_PONGVIEW_H
#define PONG_PONGVIEW_H

class PongView{

public:
  PongView(unsigned field_size_x, unsigned field_size_y, unsigned paddle_size){
    this->field_size_x = field_size_x;
    this->field_size_y = field_size_y;
    this->paddle_size = paddle_size;
  }
  virtual ~PongView(){}
    virtual int get_height_update_l() = 0;
    virtual int get_height_update_r()= 0;
  virtual void updateView(int left_paddle_pos, int right_paddle_pos,
    int ball_Pos_x, int ball_Pos_y, int score_left, int score_right) = 0; //-1 in argument doesnt update View

protected:
      unsigned field_size_x, field_size_y;
      unsigned paddle_size;
};

#endif //PONG_PONGVIEW_H
