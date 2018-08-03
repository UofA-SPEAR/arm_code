#ifndef StepperAmis_h
#define StepperAmis_h

#include "AMIS30543.h"
#include "StepperC.h"

#include "stdint.h"

class StepperAmis: public Motor {
    public:
        Stepper* p_stepper;
        AMIS30543 amis;
        int ssPin;
        
        StepperAmis(Stepper* stepper, int ssPin);
        void rotateToRadian(uint32_t target);
};

#endif
