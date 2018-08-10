#ifndef DCPotMotor_h
#define DCPotMotor_h
#include "FastPID.h"
#include "DCMotor.h"

class DCPotMotor: public DCMotor {

        uint8_t maxDutyCycle;

    public:
        int potPin;
        uint32_t lowerBoundPot; // lowest value reached in the pot's range
        uint32_t upperBoundPot; // highest value reached in the pot's range
        uint32_t potPosition;

        // PID tuning parameters
        double Kp;
        double Ki;
        double Kd;
        double Hz;

        FastPID pid;

        DCPotMotor() {}
        DCPotMotor (int dirPin, int pwmPin, int potPin, uint8_t maxDutyCycle, uint32_t lowerBoundPot, uint32_t upperBoundPot);
        void setPIDParams (double Kp, double Ki, double Kd, double Hz);
        void updatePosition();
        void home();
        void rotateTowardsRadian(uint32_t target_radian);
        void rotateToRadian(uint32_t target_radian);
};
#endif
