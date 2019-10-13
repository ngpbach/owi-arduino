#include <Arduino.h>
#include "pid.hh"

PID::PID(float _kp, float _ki, float _kd):
    kp(_kp), ki(_ki), kd(_kd) {}

void PID::setGain(float _kp, float _ki, float _kd) {
    kp = _kp;
    ki = _ki;
    kd = _kd;
}

void PID::reset() {
    err = 0.0;
    prevErr = 0.0;
    accmlErr = 0.0;
}

float PID::pidCal(float _val, float _refVal) {
    val = _val;
    refVal = _refVal;
    prevErr = err;
    err = val - refVal;

    // return 0 if set point has been reached within accuracy of 1 degree
    if (fabs(err) < 1.0 && fabs(err-prevErr) < 1.0 ) {
        reset();
        return 0.0;
    }

    accmlErr = accmlErr + err;
    if (ki*accmlErr > 0.5) accmlErr = 0.5/ki; //anti windup

    gain = kp*err + ki*accmlErr + kd*(err-prevErr);
    if (gain < -1.0) gain = -1.0;
    if (gain > 1.0) gain = 1.0;
    return gain;
}