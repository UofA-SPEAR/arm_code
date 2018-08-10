#include "DCMotor.h"

#include "Arduino.h"

DCMotor::DCMotor (int dirPin, int pwmPin, int limitSwitchPin, int encoderPinA, int pulsesPerRevolution, uint8_t dutyCycle, uint32_t lowerBound, uint32_t upperBound) {
    this->dirPin = dirPin;
    this->pwmPin = pwmPin;
    this->limitSwitchPin = limitSwitchPin;
    this->encoderPinA = encoderPinA;
    this->pulsesPerRevolution = pulsesPerRevolution;
    this->dutyCycle = dutyCycle;
    this->lowerBound = lowerBound;
    this->upperBound = upperBound;

    pinMode(this->dirPin, OUTPUT);
    pinMode(this->pwmPin, OUTPUT);
    pinMode(this->limitSwitchPin, INPUT_PULLUP);
    pinMode(this->encoderPinA, INPUT);
    
    // for safety, ensure motor does not start moving when instantiated
    this->powerOff();

    this->encoderStepPosition = 0;
    this->current_motor_radian = 0;

    // default forwardDirection to HIGH
    this->setForwardDirection(true);
}

void DCMotor::powerOn (bool dir, uint8_t dutyCycle) {
// powers the motor in specified direction and duty cycle
// if dir is true, motor will move in forwardDirection
// duty cycle should be between 0 (always off) and 255 (always on)

    this->direction = dir;

    if (dir) {
        digitalWrite(this->dirPin, this->forwardDirection);
        analogWrite(this->pwmPin, dutyCycle);
    }
    else {
        digitalWrite(this->dirPin, this->reverseDirection);
        analogWrite(this->pwmPin, dutyCycle);
    }
}

void DCMotor::powerOff () {
// stops power being sent to the motor (stops the motor)
    digitalWrite(this->pwmPin, LOW);
}

void DCMotor::home () {
// moves motor in false direction until interrupted by limit switch
// ENSURE YOU HAVE SET UP THE INTERRUPT BEFORE CALLING THIS FUNCTION

    if (digitalRead(this->limitSwitchPin) == LOW) {
        this->encoderStepPosition = 0;
        return;
    }

    this->encoderStepPosition = this->pulsesPerRevolution;
    this->rotateTowardsRadian(0);

}

void DCMotor::updatePosition () {
// this function should be called by interrupt every time encoderPinA RISES    

    if (this->direction == this->forwardDirection) {
        this->encoderStepPosition++;
    } else {
        this->encoderStepPosition--;
    }

    // encoderStepPosition should be a positive integer between 0 and this->pulsesPerRevolution
    if (this->encoderStepPosition < 0) {
        // make it positive if it's negative
        this->encoderStepPosition = this->pulsesPerRevolution + this->encoderStepPosition;
    }
    this->encoderStepPosition = fmod(this->encoderStepPosition, this->pulsesPerRevolution);

    // update current_motor_radian
    this->current_motor_radian = (double) (this->encoderStepPosition) / (double) (this->pulsesPerRevolution) * UINT32_MAX;
}

void DCMotor::rotateTowardsRadian (uint32_t target_radian) {
// Given a target angle, calculates the corresponding encoder position and direction in which the motor needs to move
// Moves the motor in that direction for 10 milliseconds or until it reaches the desired encoder position, whichever comes first

    // get the start time
    uint32_t startTime = millis();

    // constrain to motor bounds
    target_radian = constrain(target_radian, this->lowerBound, this->upperBound);

    // calculate target radian in terms of encoder steps
    // this is important because if you do it in terms of a UINT32_t target radian, you might never reach that exact target radian
    int targetEncoderStepPosition = (double)(target_radian) / (double)(UINT32_MAX) * this->pulsesPerRevolution;

    // Fixes bug where motor would keep turning forever if given an angle on or near 360 degrees
    // Since this->encoderStepPosition is modded with this->pulsesPerRevolution, it is never equal to this->pulsesPerRevolution. It gets to this->pulsesPerRevolution - 1, then is reset back to zero. Therefore, we must always use 0 instead of this->pulsesPerRevolution or else the code below will think that the motor never reaches its target position.
    if (targetEncoderStepPosition == this->pulsesPerRevolution) {
        targetEncoderStepPosition = 0;
    }

    // calculate the most efficient path to target angle
    // only perform optimization if the motor can rotate freely through 360 degrees
    int64_t encoderStepDiff = ((int64_t)targetEncoderStepPosition) - ((int64_t)this->encoderStepPosition);

    if (this->lowerBound == 0 && this->upperBound == UINT32_MAX) {
        if(encoderStepDiff > this->pulsesPerRevolution/2){
            encoderStepDiff = encoderStepDiff - this->pulsesPerRevolution;
        }
        if(encoderStepDiff < 0 && abs(encoderStepDiff) > abs(this->pulsesPerRevolution/2)){
            encoderStepDiff = this->pulsesPerRevolution + encoderStepDiff;
        }
    }

    // determine direction
    bool dir;
    if (encoderStepDiff > 0) {
        dir = true;
    } else {
        dir = false;
    }
    
    // while encoder is not at target and 10ms have not passed
    while(millis() - startTime < 10) {
        if (this->encoderStepPosition != targetEncoderStepPosition){
            this->powerOn(dir, this->dutyCycle);
        }
    }
    this->powerOff();

}

void DCMotor::rotateToRadian (uint32_t target_radian) {
// Given a target angle, calculates the corresponding encoder position and direction in which the motor needs to move
// Moves to motor in that direction until it reaches the desired encoder position 

    // constrain to motor bounds
    target_radian = constrain(target_radian, this->lowerBound, this->upperBound);

    // calculate target radian in terms of encoder steps
    // this is important because if you do it in terms of a UINT32_t target radian, you might never reach that exact target radian
    int targetEncoderStepPosition = (double)(target_radian) / (double)(UINT32_MAX) * this->pulsesPerRevolution;

    // if motor cannot rotate through the full 360 degrees, use a different algorithm which will always stay inside those bounds
    if (this->lowerBound != 0 || this->upperBound != UINT32_MAX) {
        bool dir;
        if (targetEncoderStepPosition > this->encoderStepPosition) {
            dir = true;
        } else if (targetEncoderStepPosition < this->encoderStepPosition) {
            dir = false;
        }

        while (this->encoderStepPosition != targetEncoderStepPosition) {
            this->powerOn(dir, this->dutyCycle);
        }
        this->powerOff();
 
        return;
    }

    // Fixes bug where motor would keep turning forever if given an angle on or near 360 degrees
    // Since this->encoderStepPosition is modded with this->pulsesPerRevolution, it is never equal to this->pulsesPerRevolution. It gets to this->pulsesPerRevolution - 1, then is reset back to zero. Therefore, we must always use 0 instead of this->pulsesPerRevolution or else the code below will think that the motor never reaches its target position.
    if (targetEncoderStepPosition == this->pulsesPerRevolution) {
        targetEncoderStepPosition = 0;
    }

    // calculate the most efficient path to target angle
    int encoderStepDiff = (targetEncoderStepPosition - this->encoderStepPosition);

    if(encoderStepDiff > this->pulsesPerRevolution/2){
        encoderStepDiff = encoderStepDiff - this->pulsesPerRevolution;
    }
    if(encoderStepDiff < -1*this->pulsesPerRevolution/2){
        encoderStepDiff = this->pulsesPerRevolution + encoderStepDiff;
    }

    // power the motor until it reaches the target angle
    // choose the direction based on whether encoderStepDiff is positive or negative
    if (encoderStepDiff != 0) { // this fixes bug where motor is at zero degrees and given target angle 360 degrees
        if (encoderStepDiff>0) {
            while (this->encoderStepPosition != targetEncoderStepPosition) {
                this->powerOn(true, this->dutyCycle);
            }
        } else {
            while (this->encoderStepPosition != targetEncoderStepPosition) {
                this->powerOn(false, this->dutyCycle);
            }
        }
    }
    this->powerOff();
}
