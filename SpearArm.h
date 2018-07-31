#ifndef Speararm_h
#define Speararm_h
#include "Motor.h"
#include "StepperC.h"
#include "DCMotor.h"
#include "DCPotMotor.h"
#include <stdint.h>

class Arm{
    
    // motors should be a pointer to an array of 6 motor pointers
    Motor** motors;

    public:
        Arm(Motor* motors[6]);
        void armTo(uint32_t *targets);
};

#endif
