#include "DCPotMotor.h"

#include "Arduino.h"

DCPotMotor::DCPotMotor (int dirPin, int pwmPin, int potPin, uint32_t lowerBoundPot, uint32_t upperBoundPot) {
    this->dirPin = dirPin;
    this->pwmPin = pwmPin;
    this->potPin = potPin;
    this->lowerBoundPot = lowerBoundPot;
    this->upperBoundPot = upperBoundPot;
    this->lowerBound = 0;
    this->upperBound = UINT32_MAX;

    pinMode(this->dirPin, OUTPUT);
    pinMode(this->pwmPin, OUTPUT);

    this->potPosition = analogRead(this->potPin);

    // set forwardDirection to HIGH by default
    this->setForwardDirection(true);
}

void DCPotMotor::updatePosition () {
// reads absolute position from potentiometer
// this function should be called repeatedly in a loop
    this->potPosition = analogRead(this->potPin);
}

void DCPotMotor::rotateTowardsRadian (uint32_t target_radian) {
// given a target angle, calculates the corresponding potentiometer position and rotates the motor in the correct direction for 10 milliseconds or until it reaches that position, whichever comes first

    // get start time
    uint32_t startTime = millis();

    // calculate target position in terms of potentiometer position
    target_radian = constrain(target_radian, this->lowerBound, this->upperBound);
    uint16_t targetPotPosition = (target_radian - this->lowerBound) * ((double)(this->upperBoundPot - this->lowerBoundPot) / (double)(this->upperBound - this->lowerBound)) + this->lowerBoundPot;

    // constrain once more in case floating point errors have caused targetPotPosition to be out of range
    targetPotPosition = constrain(targetPotPosition, this->lowerBoundPot, this->upperBoundPot);

    // return early if already at targetPotPosition
    this->updatePosition();
    if (this->potPosition == targetPotPosition) {
        return;
    }

    // determine direction towards target position
    bool dir;
    if (targetPotPosition > this->potPosition) {
        dir = true;
    } else {
        dir = false;
    }

    // move until motor reaches target position or 10 milliseconds have elapsed
    while((millis() - startTime < 10) && this->potPosition != targetPotPosition) {
        this->powerOn(dir, this->dutyCycle);
        this->updatePosition();
    }
    this->powerOff();
}

void DCPotMotor::rotateToRadian (uint32_t target_radian) {
// given a target angle, calculates the corresponding potentiometer position and rotates the motor in the correct direction until it reaches that position

    // calculate target angle in terms of a potentiometer reading
    // arduino reads an integer from 0 to 1023 from analog pins 
    // for now, assume that the range of motion of the potentiometer is a full 360 degrees
    uint32_t targetPotPosition = (double)(target_radian) / (double)(UINT32_MAX) * 1023;

    // constrain to the range of reachable values on the pot
    targetPotPosition = constrain(targetPotPosition, this->lowerBoundPot, this->upperBoundPot);

    // if motor is already at the target position, do nothing
    if (targetPotPosition == this->potPosition) {
        return;
    }

    // decide which direction the motor needs to turn to reach target
    bool dir;
    if (targetPotPosition > this->potPosition) {
        dir = true;
    } else {
        dir = false;
    }

    // move the motor in the necessary direction until it reaches targetPotPos
    this->powerOn(dir, this->dutyCycle);
    while (this->potPosition != targetPotPosition) {
        this->updatePosition();
    }
    this->powerOff();

}
