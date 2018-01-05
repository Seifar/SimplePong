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

#define PORT_SERVER 5555
#define PORT_CLIENT 5556

class PongSocket : public PongView{
public:
    PongSocket(unsigned int field_size_x, unsigned int field_size_y, unsigned int paddle_size);
    ~PongSocket();

    void updateView(int left_paddle_pos, int right_paddle_pos,
                    int ball_Pos_x, int ball_Pos_y, int score_left, int score_right) override; //-1 in argument doesnt update View
    int get_height_update_r() override;
    int get_height_update_l() override;

private:
    //TODO man braucht 4 sockets (beide seiten eine AI)
    int sockfd_sensor, //server
            sockfd_motor; //client
    int portno_sensor;
    socklen_t clilen_sensor;
    char buffer_sensor[256];
    struct sockaddr_in6 serv_addr_sensor, cli_addr_sensor;
    int n_sensor;
    char client_addr_ipv6_sensor[100];

    int setup_sensor_server();
    int stop_sensor_server();

    int setup_motor_client();
    int stop_motor_client();
};


#endif //PONG_PONGSOCKET_H
