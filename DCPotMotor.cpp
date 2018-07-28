#include "DCPotMotor.h"

#include "Arduino.h"

DCPotMotor::DCPotMotor (int dirPin, int pwmPin, int potPin, uint32_t lowerBound, uint32_t upperBound) {
    this->dirPin = dirPin;
    this->pwmPin = pwmPin;
    this->potPin = potPin;
    this->lowerBound = lowerBound;
    this->upperBound = upperBound;

    pinMode(this->dirPin, OUTPUT);
    pinMode(this->pwmPin, OUTPUT);
}

void DCPotMotor::updatePosition () {
// reads absolute position from potentiometer
// this function should be called repeatedly in a loop
    this->potPosition = analogRead(this->potPin);
}

void rotateToRadian (uint32_t target_radian) {
    return;
}
