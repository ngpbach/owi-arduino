#include "Arduino.h"
#include "motor.hh"

MOTOR::MOTOR() {

}

void MOTOR::update(dir direction, uint8_t power) {
    setDirection(direction);
    setPower(power);
}

void MOTOR::setDirection(dir direction) {
    Dir = direction;
}

void MOTOR::setPower(uint8_t power) {
    pwm = power;
}

L298N::L298N(uint8_t enPin, uint8_t in1Pin, uint8_t in2Pin) :
             enP(enPin), in1P(in1Pin), in2P(in2Pin), dur(0) {
    pinMode(enP, OUTPUT);
    pinMode(in1P, OUTPUT);
    pinMode(in2P, OUTPUT);
}

void L298N::setDuration(long duration) {
    dur = duration;
}

void L298N::output() {
    switch (Dir) {
        case dir::CW:
            digitalWrite(in1P, 0);
            digitalWrite(in2P, 1);
            break;

        case dir::CCW:
            digitalWrite(in1P, 1);
            digitalWrite(in2P, 0);
            break;

        default:
            break;
    }

    analogWrite(enP, pwm);

    if (dur != -1) {
       delay(dur);
       analogWrite(enP, 0);
    }
}

void L298N::reverse() {
    if (Dir == dir::CW) {
        Dir = dir::CCW;
    } else {
        Dir = dir::CW;
    }

    output();
}