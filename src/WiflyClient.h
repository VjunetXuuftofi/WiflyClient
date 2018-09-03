//
// Created by thomas on 9/3/18.
//

#ifndef WIFLYCLIENT_H
#define WIFLYCLIENT_H

#endif

#include "SpiUart.h"


class WiflyClient {
public:
    WiflyClient(bool debug);

    void send_command(char* command);
    void send_command(char* command, unsigned long delay_time);

    void join_network(char* network_ssid);
    void join_network(char* network_ssid, char* password);

    void open_connection(char* address);

    void make_request(char* request);

    void enter_command_mode();

    bool output_available();

    char read_char_from_output();


    bool _debug;
    char _last_read;

    SpiUartDevice SpiSerial;
};
