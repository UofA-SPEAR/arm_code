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
#define WRIST_ROLL 4
#define FINGERS 5


class Arm{
    
    // motors should be a pointer to an array of 6 pointers to Motor objects
    // This is done because the DCMotor, DCPotMotor, and Stepper classes are pointer-compatible
    //   therefore we can write the Arm class without caring what specific type of motor each one is.
    Motor** motors;

    public:

        Stepper baseMotor;
        DCPotMotor shoulderMotor;
        Stepper elbowMotor;
        Stepper wristPitchMotor;
        DCMotor wristRollMotor;
        DCMotor fingersMotor;

        Arm();
        void armTo(uint32_t *targets);
};

#endif
