#include "Arduino.h"

#include "Motor.h"

void Motor::setForwardDirection(bool selection) {
// method to easily set what value for the dir pin is considered forward (increasing angles)

    if (selection) {
        this->forwardDirection = HIGH;
        this->reverseDirection = LOW;
    } else {
        this->forwardDirection = LOW;
        this->reverseDirection = HIGH;
    }
}
