// class for DC Motor with encoder

#include "Motor.h"

#include <stdint.h>

class DCMotor: public Motor {

    public:
        int dirPin;
        int pwmPin;
        int encoderPinA;
        int encoderPinB;
        int pulsesPerRevolution;

        bool direction;
        int encoderStepPosition;

        DCMotor (int dirPin, int pwmPin, int encoderPinA, int encoderPinB, int pulsesPerRevolution, uint32_t lowerBound, uint32_t upperBound);
        void powerOn (bool dir, uint8_t dutyCycle);
        void powerOff ();
        void updateEncoderPosition ();
        void rotateToRadian (uint32_t target_angle);
};
