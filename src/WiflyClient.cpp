//
// Created by thomas on 9/3/18.
//
#include "WiflyClient.h"

WiflyClient::WiflyClient(bool debug) {
    _debug = debug;
    if (debug) {
        Serial.begin(9600);
    }
    SpiSerial.begin();
}



void WiflyClient::send_command(char *command) {
    send_command(command, 500);
}
void WiflyClient::send_command(char *command, unsigned long delay_time) {
    for (int i = 0; command[i] != '\0'; ++i) {
        SpiSerial.write((int) command[i]);
    }
    delay(delay_time);
    while(SpiSerial.available() > 0) {
        int char_read = SpiSerial.read();
        if (_debug) {
            Serial.write(char_read);
        }
    }
};

void WiflyClient::join_network(char *network_ssid) {
    enter_command_mode();
    send_command((char*) "join ");
    send_command(network_ssid);
    send_command((char*)"\r");
    send_command((char*)"set ip proto 18\r");
    send_command((char*)"set ip address 0\r");
    send_command((char*)"set ip remote 80\r");
    send_command((char*)"set com remote 0\r");
}

void WiflyClient::join_network(char *network_ssid, char *password) {
    enter_command_mode();
    send_command((char*) "set wlan pass ");
    send_command(password);
    send_command((char*)"\r");
    join_network(network_ssid);
}



void WiflyClient::open_connection(char *address) {
    enter_command_mode();
    send_command((char*)"set dns name ");
    send_command(address);
    send_command((char*) "\r");

    send_command((char*)"open ");
    send_command(address);
    send_command((char*) " 80\r", 10000);
}

void WiflyClient::make_request(char *request) {
    for (int i = 0; request[i] != '\0'; ++i) {
        SpiSerial.write((int) request[i]);
    }
}


bool WiflyClient::output_available() {
    // We need to read from the incoming stream as fast as we can. Otherwise, we lose it (it looks like SpiSerial can
    // only hold so much).
    // However, the stream is not usually loaded as fast as we can read it, so we need to have some delay.
    // The loop below checks for availability every millisecond for up to five seconds.
    for (int i = 0; i < 5000; i ++ ) {
        if (SpiSerial.available() > 0) {
            return true;
        }
        delay(1);
    }
    return false;
}

char WiflyClient::read_char_from_output() {
    return (char) SpiSerial.read();
}

void WiflyClient::enter_command_mode() {
    // the following is to get us into command mode
    send_command((char*)"$$$");
    // sometimes, we are already in command mode for some reason I can't explain.
    // in this case the dollar signs won't do anything, and will just corrupt
    // the next input. To prevent this, we send a meaningless command followed
    // by a carriage return. If we were in command mode from the start, the invalid
    // command will get rid of the dollar signs. If we weren't, it'll just fail but
    // that's fine.
    send_command((char*)"invalid_command\r");
}