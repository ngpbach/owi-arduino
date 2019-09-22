#include <Arduino.h>
#include "SerialHelper.hh"

oLoopCtrl getCtrInput() {
    oLoopCtrl recv = {};
    
    Serial.print("!!!Data has to be sent with endline character!!!\n");

    int number = -1;
    while (number < 0 || number > 4) {
        Serial.print("\nEnter joint index\n");
        number = getInt();
    }
    recv.i = number;

    number = -1;
    while (number != 0 && number != 1) {
        Serial.print("\nEnter direction (0/1)\n");
        number = getInt();
    }
    recv.direction = static_cast<motor::dir>(number);

    number = -1;
    while (number < 0 || number > 255) {
        Serial.print("\nEnter power (0-255)\n");
        number = getInt();
    }
    recv.pwm = number;

    number = -1;
    while (number < 0) {
        Serial.print("\nEnter duration (ms)\n");
        number = getInt();
    }
    recv.duration = number;

    return recv;
}

int getInt() {
    char buffer[32];

    while(!Serial.available()); //spin and wait for incoming data
    int length = Serial.readBytesUntil('\n', buffer, 31);
    buffer[length] = '\0';      //terminate received string
    int number = atoi(buffer);
    Serial.println(number);
    return number;
}
