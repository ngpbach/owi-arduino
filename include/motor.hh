#ifndef MOTOR_HH
#define MOTOR_HH

#include <stdint.h>

/**
 * Abstract motor driver class
 */
class MOTOR {
public:

    /** 
     * direction of movement, implementation defined
     * POS - positive direction
     * NEG - negative direction
    */
    enum class DIR {
        POS,
        NEG
    };

    /**
     * Constructor
     */
    MOTOR();

    /**
     * new control parametters 
     */
    void update(DIR direction, uint8_t power);

    /**
     *  perform the motion
     */
    virtual void output() = 0;

    /** set rotational direction */
    void setDirection(DIR direction);

    /** set duty cycle */
    void setPower(uint8_t power);

protected:

    /** rotation direction */
    DIR dir{DIR::POS};

    /** duty cycle (0-255) */
    uint8_t pwm{0};

    /** rotational position */
    float pos{0.0};

    /** home position */
    const float homePos{0.0};

    /** target position */
    float targetPos{0.0};
};

/**
 * L298N motor driver with arduino
 */
class L298N : public MOTOR {
public:

    /**
     * Constructor
     */
    L298N(uint8_t enPin, uint8_t in1Pin, uint8_t in2Pin);

    /**
     * set duration of the motion
     * @param duration time motor run in ms
     */
    void setDuration(long duration);
    
    /**
     * perform the motion for set duration
     * if dur == -1 drive in continous mode
     * (WARNING: continous mode will output non stop,
     * need to be called repeatedly to change speed/stop)
     */
    void output() override;

    /**
     * perform reverse of last motion
     */
    void reverse();

private:

    /** enable (PWM) pin */
    const uint8_t enP;

    /** direction pin 1 */
    const uint8_t in1P;

    /** direction pin 2 */
    const uint8_t in2P;

    /** duration of motion */
    long dur;

}; //class MOTOR

#endif //MOTOR_HH
