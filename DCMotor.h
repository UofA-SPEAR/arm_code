// class for DC Motor with encoder

#ifndef DCMotor_h
#define DCMotor_h
#include "Motor.h"

#include <stdint.h>

class DCMotor: public Motor {

    public:
        int dirPin;
        int pwmPin;
        int limitSwitchPin;
        int encoderPinA;
        int pulsesPerRevolution;
        uint8_t dutyCycle;

        bool direction;
        int encoderStepPosition;

        DCMotor () {}
        DCMotor (int dirPin, int pwmPin, int limitSwitchPin, int encoderPinA, int pulsesPerRevolution, uint8_t dutyCycle, uint32_t lowerBound, uint32_t upperBound);
        void powerOn (bool dir, uint8_t dutyCycle);
        void powerOff ();
        void home ();
        void updatePosition ();
        virtual void rotateTowardsRadian (uint32_t target_angle);
        virtual void rotateToRadian (uint32_t target_angle);
};
#endif
