//
// Created by thomas on 06.12.17.
//

#ifndef PONG_PONGSOCKET_H
#define PONG_PONGSOCKET_H


#include "PongView.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <arpa/inet.h>

#define PORT 5555

class PongSocket : public PongView{
public:
    PongSocket(unsigned int field_size_x, unsigned int field_size_y, unsigned int paddle_size);

    void updateView(int left_paddle_pos, int right_paddle_pos,
                    int ball_Pos_x, int ball_Pos_y, int score_left, int score_right) override; //-1 in argument doesnt update View
    int get_height_update_r() override;
    int get_height_update_l() override;

private:
    int sockfd_sensor, //server
            socked_motor; //client
    int portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in6 serv_addr, cli_addr;
    int n;
    char client_addr_ipv6[100];

    int setup_sensor_server();
    int stop_sensor_server();
};


#endif //PONG_PONGSOCKET_H
