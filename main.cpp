#include "SpearArm.h"
#include "StepperC.h"
#include "StepperAmis.h"
#include "Motor.h"
#include "DCMotor.h"
#include "DCPotMotor.h"

#include <Arduino.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

// arm needs to be a global variable since the motors need to be modified by interrupt functions
Arm* arm;

// define interrupt positions for encoders on DC motors and limit switches on DC motors
void updatePositionWristRoll () {
// read encoder position every time a pulse is received
    arm->wristRollMotor.updatePosition();
}
void zeroWristRoll () {
// set encoderStepPosition to zero when the end stop is hit
    arm->wristRollMotor.powerOff();
    arm->wristRollMotor.encoderStepPosition = 0;
}
void updatePositionFingers() {
    arm->fingersMotor.updatePosition();
}
void zeroFingers() {
    arm->fingersMotor.powerOff();
    arm->fingersMotor.encoderStepPosition = 0;
}

// define interrupt functions for limit switches on stepper motors
void zeroElbow() {
    arm->elbowMotor.current_motor_radian = 0;
}

void setup(){
	init();
    SPI.begin();
	Serial.begin(9600);
	Serial.println("Initalized");
    delay(1000);

}

void attachInterrupts() {
    // attach interrupts for DC motors with encoders and limit switches
    attachInterrupt(digitalPinToInterrupt(arm->wristRollMotor.encoderPinA), updatePositionWristRoll, RISING);
    attachInterrupt(digitalPinToInterrupt(arm->wristRollMotor.limitSwitchPin), zeroWristRoll, FALLING);  
    attachInterrupt(digitalPinToInterrupt(arm->fingersMotor.encoderPinA), updatePositionFingers, RISING);
    attachInterrupt(digitalPinToInterrupt(arm->fingersMotor.limitSwitchPin), zeroFingers, FALLING);

    // attach interrupts for stepper motors with limit switches
    attachInterrupt(digitalPinToInterrupt(arm->elbowMotor.limitSwitchPin), zeroElbow, FALLING);
}

int main(){
	setup();
    arm = new Arm();
    attachInterrupts();
    arm->wristPitchMotor.setForwardDirection(false);

    // initialize steppers that use the amis driver
    StepperAmis baseMotorAmis(41, 2000);
    StepperAmis elbowMotorAmis(42, 2000);

	uint32_t buffer[6];
    for(;;){
        if (Serial.available() >= 24) {
            Serial.readBytes((char *)buffer, sizeof(uint32_t)*6);
        }
        arm->baseMotor.rotateTowardsRadian(buffer[BASE]);
        arm->elbowMotor.rotateTowardsRadian(buffer[ELBOW]);
        arm->wristRollMotor.rotateTowardsRadian(buffer[WRIST_ROLL]);
        arm->fingersMotor.rotateTowardsRadian(buffer[FINGERS]);
        Serial.println(arm->fingersMotor.encoderStepPosition);
    }

	return 0;
}
