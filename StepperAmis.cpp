#include "Arduino.h"
#include "StepperAmis.h"

StepperAmis::StepperAmis(Stepper* p_stepper, int ssPin) {
    this->p_stepper = p_stepper;
    this->ssPin = ssPin;

    this->amis.init(this->ssPin);
    this->amis.setStepMode(1);
    this->amis.enableDriver();
    this->amis.setCurrentMilliamps(1500);
}
void StepperAmis::rotateToRadian(uint32_t target) {
    this->p_stepper->rotateToRadian(target);
}
