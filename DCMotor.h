// class for DC Motor with encoder

#include "Motor.h"

#include <stdint.h>

class DCMotor: public Motor {

    public:
        int dirPin;
        int pwmPin;

        DCMotor (int dirPin, int pwmPin, uint32_t lowerBound, uint32_t upperBound);
        void powerOn (bool dir, uint8_t dutyCycle);
        void powerOff ();
        void rotateToRadian (uint32_t target_angle);
};
