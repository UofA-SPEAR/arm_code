#include "DCMotor.h"

#include "Arduino.h"

DCMotor::DCMotor (int dirPin, int pwmPin, int encoderPinA, int encoderPinB, int pulsesPerRevolution, uint32_t lowerBound, uint32_t upperBound) {
    this->dirPin = dirPin;
    this->pwmPin = pwmPin;
    this->encoderPinA = encoderPinA;
    this->encoderPinB = encoderPinB;
    this->pulsesPerRevolution = pulsesPerRevolution;
    this->lowerBound = lowerBound;
    this->upperBound = upperBound;

    pinMode(this->dirPin, OUTPUT);
    pinMode(this->pwmPin, OUTPUT);
    pinMode(this->encoderPinA, INPUT);
    pinMode(this->encoderPinB, INPUT);
    
    // for safety, ensure motor does not start moving when instantiated
    this->powerOff();

    // read starting state of encoder
    this->aLastState = digitalRead(this->encoderPinA);
    this->encoderStepPosition = 0;
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

void DCMotor::updateEncoderPosition () {
    this->aState = digitalRead(this->encoderPinA);
    
    // check if state of signal A has changed
    if (this->aState != this->aLastState) {

        // compare with signal B to decide which direction the motor turned
        if (digitalRead(this->encoderPinB) != this->aState) {
            this->encoderStepPosition++;
        } else {
            this->encoderStepPosition--;
        }

    }
    
    this->aLastState = this->aState;
}

void DCMotor::rotateToRadian (uint32_t target_radian) {
    return;
}
