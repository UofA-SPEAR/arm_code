#ifndef StepperAmis_h
#define StepperAmis_h

#include "AMIS30543.h"

#include "stdint.h"

class StepperAmis {
    public:
        AMIS30543 amis;
        int ssPin;
        uint16_t currentLimit;
        
        StepperAmis(int ssPin, uint16_t currentLimit);
};

#endif
