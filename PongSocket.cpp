//
// Created by thomas on 06.12.17.
//

#include "PongSocket.h"


#include <iostream>

PongSocket::PongSocket(unsigned int field_size_x, unsigned int field_size_y, unsigned int paddle_size)
        : PongView(field_size_x, field_size_y, paddle_size) {

    if (!setup_server())
        exit(-1);




}



int PongSocket::get_height_update_r() {

}

int PongSocket::get_height_update_l() {

}

void PongSocket::updateView(int left_paddle_pos, int right_paddle_pos, int ball_Pos_x, int ball_Pos_y, int score_left,
                            int score_right) {

}

int PongSocket::setup_sensor_server() {
    printf("\nIPv6 TCP Server Started...\n");

    sockfd_sensor = socket(AF_INET6, SOCK_STREAM, 0);
    if(sockfd_sensor < 0){
        std::cout << "Error opening socket\n";
        return(-1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = PORT;
    serv_addr.sin6_flowinfo = 0;
    serv_addr.sin6_family = AF_INET6;
    serv_addr.sin6_addr = in6addr_any;
    serv_addr.sin6_port = htons(portno);

    //Sockets Layer Call: bind()
    if (bind(sockfd_sensor, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("ERROR on binding");
        return 0;
    }

    //Sockets Layer Call: listen()
    listen(sockfd_sensor, 5);
    clilen = sizeof(cli_addr);

    //Sockets Layer Call: accept()
    int tmp = sockfd_sensor;
    sockfd_sensor = accept(sockfd_sensor, (struct sockaddr *) &cli_addr, &clilen);
    close(tmp);
    if (sockfd_sensor < 0){
        printf("ERROR on accept");
        return -1;
    }

    //Sockets Layer Call: inet_ntop()
    inet_ntop(AF_INET6, &(cli_addr.sin6_addr),client_addr_ipv6, 100);
    printf("Incoming connection from client having IPv6 address: %s\n",client_addr_ipv6);

    memset(buffer,0, 256);

    //send how many input neurons are needed

}

int PongSocket::stop_sensor_server(){
    close(sockfd_sensor);
}


