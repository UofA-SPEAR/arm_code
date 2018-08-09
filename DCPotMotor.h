#ifndef DCPotMotor_h
#define DCPotMotor_h
#include "DCMotor.h"

class DCPotMotor: public DCMotor {

    public:
        int potPin;
        uint32_t lowerBoundPot; // lowest value reached in the pot's range
        uint32_t upperBoundPot; // highest value reached in the pot's range
        uint32_t potPosition;

        DCPotMotor() {}
        DCPotMotor (int dirPin, int pwmPin, int potPin, uint32_t lowerBoundPot, uint32_t upperBoundPot);
        void updatePosition();
        void rotateTowardsRadian(uint32_t target_radian);
        void rotateToRadian(uint32_t target_radian);
};
#endif
