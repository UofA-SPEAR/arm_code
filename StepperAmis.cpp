#include "common.h"
#include "StepperAmis.h"

StepperAmis::StepperAmis(int ssPin, uint16_t currentLimit) {
    this->ssPin = ssPin;
    this->currentLimit = currentLimit;

    this->amis.init(this->ssPin);
    this->amis.setStepMode(1);
    this->amis.enableDriver();
    this->amis.setCurrentMilliamps(this->currentLimit);
}
