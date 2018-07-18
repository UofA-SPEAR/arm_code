#include "DCMotor.h"

#include "Arduino.h"

DCMotor::DCMotor (int dirPin, int pwmPin, uint32_t lowerBound, uint32_t upperBound) {
    this->dirPin = dirPin;
    this->pwmPin = pwmPin;
    this->lowerBound = lowerBound;
    this->upperBound = upperBound;

    pinMode(this->dirPin, OUTPUT);
    pinMode(this->pwmPin, OUTPUT);
    
    // for safety, ensure motor does not start moving when instantiated
    this->powerOff();
}

void DCMotor::powerOn (bool dir, uint8_t dutyCycle) {
// powers the motor in specified direction and duty cycle
// duty cycle should be between 0 (always off) and 255 (always on)
    if (dir) {
        digitalWrite(this->dirPin, HIGH);
        analogWrite(this->pwmPin, dutyCycle);
    }
    else {
        digitalWrite(this->dirPin, LOW);
        analogWrite(this->pwmPin, dutyCycle);
    }
}

void DCMotor::powerOff () {
// stops power being sent to the motor (stops the motor)
    digitalWrite(this->pwmPin, LOW);
}

void DCMotor::rotateToRadian (uint32_t target_radian) {
    return;
}
