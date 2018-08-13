#include "DCPotMotor.h"

#include "common.h"

DCPotMotor::DCPotMotor (int dirPin, int pwmPin, int potPin, uint8_t maxDutyCycle, uint32_t lowerBoundPot, uint32_t upperBoundPot) {
    this->dirPin = dirPin;
    this->pwmPin = pwmPin;
    this->potPin = potPin;
    this->maxDutyCycle = maxDutyCycle;
    this->lowerBoundPot = lowerBoundPot;
    this->upperBoundPot = upperBoundPot;
    this->lowerBound = 0;
    this->upperBound = UINT32_MAX;

    this->Kp = 0;
    this->Ki = 0;
    this->Kd = 0;

    pinMode(this->dirPin, OUTPUT);
    pinMode(this->pwmPin, OUTPUT);

    this->potPosition = analogRead(this->potPin);

    // set forwardDirection to HIGH by default
    this->setForwardDirection(true);
}

void DCPotMotor::setPIDParams (double Kp, double Ki, double Kd, double Hz) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    this->Hz = Hz;

    // Re-configure FastPID object
    this->pid.clear();
    this->pid.setCoefficients(this->Kp, this->Ki, this->Kd, this->Hz);
    this->pid.setOutputRange(-50, 50); //TODO: don't hard code the max duty cycle
}

void DCPotMotor::updatePosition () {
// reads absolute position from potentiometer
// this function should be called repeatedly in a loop
    this->potPosition = analogRead(this->potPin);
}

void DCPotMotor::home () {
// moves shoulder to a comfortable position (potentiometer position 400)
    this->rotateTowardsRadian( ((double)400) / ((double)1023) * UINT32_MAX);
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

    this->updatePosition();

    // using PID algorithm, determine appropriate duty cycle
    int16_t PIDOutput = this->pid.step(targetPotPosition, this->potPosition);

    // set direction
    bool dir;
    if (PIDOutput > 0) {
        dir = true;
    } else {
        dir = false;
        PIDOutput = abs(PIDOutput);
    }

    // move until motor reaches target position or 10 milliseconds have elapsed
    while(millis() - startTime < THREAD_DURATION) {
        this->powerOn(dir, PIDOutput);
        this->updatePosition();
    }
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
