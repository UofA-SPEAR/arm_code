// Base class for stepper and DC motors

#ifndef Motor_h
#define Motor_h
#include <stdint.h>

class Motor {

    public:
        virtual void rotateToRadian(uint32_t target_radian) = 0;

        uint32_t lowerBound;
        uint32_t upperBound;
        int direction;
        uint32_t current_motor_radian;

};
#endif
