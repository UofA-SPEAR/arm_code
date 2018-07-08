#ifndef Speararm_h
#define Speararm_h
#include "StepperC.h"
#include <stdint.h>

class Arm{

	public:
		Arm();
    void armTo(uint32_t *targets);

	private:

    //Motor instances, one should be a DC motor
		Stepper* BaseStepper;
		Stepper* ShoulderStepper;
		Stepper* ElbowStepper;
        Stepper* WristStepper;
		Stepper* FingerStepper;

};

#endif
