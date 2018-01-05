//
// Created by thomas on 06.12.17.
//

#include "PongSocket.h"


#include <iostream>

PongSocket::PongSocket(unsigned int field_size_x, unsigned int field_size_y, unsigned int paddle_size)
        : PongView(field_size_x, field_size_y, paddle_size) {

    if (!setup_sensor_server())
        exit(-1);




}

PongSocket::~PongSocket() {
    stop_sensor_server();
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

    bzero((char *) &serv_addr_sensor, sizeof(serv_addr_sensor));
    portno_sensor = PORT_SERVER;
    serv_addr_sensor.sin6_flowinfo = 0;
    serv_addr_sensor.sin6_family = AF_INET6;
    serv_addr_sensor.sin6_addr = in6addr_any;
    serv_addr_sensor.sin6_port = htons(portno_sensor);

    //Sockets Layer Call: bind()
    if (bind(sockfd_sensor, (struct sockaddr *) &serv_addr_sensor, sizeof(serv_addr_sensor)) < 0) {
        printf("ERROR on binding");
        return 0;
    }

    //Sockets Layer Call: listen()
    listen(sockfd_sensor, 5);
    clilen_sensor = sizeof(cli_addr_sensor);

    //Sockets Layer Call: accept()
    int tmp = sockfd_sensor;
    sockfd_sensor = accept(sockfd_sensor, (struct sockaddr *) &cli_addr_sensor, &clilen_sensor);
    close(tmp);
    if (sockfd_sensor < 0){
        printf("ERROR on accept");
        return -1;
    }

    //Sockets Layer Call: inet_ntop()
    inet_ntop(AF_INET6, &(cli_addr_sensor.sin6_addr),client_addr_ipv6_sensor, 100);
    printf("Incoming connection from client having IPv6 address: %s\n",client_addr_ipv6_sensor);

    memset(buffer_sensor,0, 256);

    //send how many input neurons are needed
        //ballposx ballposy ownpaddlepos
    int no_input_neurons = 3;
    if (0 > send(sockfd_sensor, &no_input_neurons, sizeof(no_input_neurons), 0)){
        return -1;
    }

    return 0;
}

int PongSocket::stop_sensor_server(){
    return close(sockfd_sensor);
}

int PongSocket::setup_motor_client() {
    return 0;
}

int PongSocket::stop_motor_client() {
    return close(sockfd_motor);
}
