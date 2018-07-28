#ifndef DCPotMotor_h
#define DCPotMotor_h
#include "DCMotor.h"

class DCPotMotor: public DCMotor {

    public:
        int potPin;
        uint32_t potPosition;

        DCPotMotor (int dirPin, int pwmPin, int potPin, uint32_t lowerBound, uint32_t upperBound);
        void updatePosition();
        void rotateToRadian(uint32_t target_radian);
};
#endif
