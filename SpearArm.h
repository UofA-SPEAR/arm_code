#ifndef Speararm_h
#define Speararm_h
#include "Motor.h"
#include "StepperC.h"
#include "DCMotor.h"
#include "DCPotMotor.h"
#include <stdint.h>



class Arm{
    
    public:

        Stepper baseMotor;
        DCPotMotor shoulderMotor;
        Stepper elbowMotor;
        Stepper wristPitchMotor;

        Arm();
        void home();
        void adjust(uint32_t *targets);
};

#endif
