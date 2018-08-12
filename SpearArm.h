#ifndef Speararm_h
#define Speararm_h
#include "Motor.h"
#include "StepperC.h"
#include "DCMotor.h"
#include "DCPotMotor.h"
#include <stdint.h>

//Constants for array index of each motor
#define BASE 0
#define SHOULDER 1
#define ELBOW 2
#define WRIST_PITCH 3

#define NUM_MOTORS 4


class Arm{
    
    public:

        Stepper baseMotor;
        DCPotMotor shoulderMotor;
        Stepper elbowMotor;
        Stepper wristPitchMotor;
        DCMotor wristRollMotor;
        DCMotor fingersMotor;

        Arm();
        void home();
        void adjust(uint32_t *targets);
        void armTo(uint32_t *targets);
};

#endif
