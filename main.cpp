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
#define UINT32_MAX 4294967295UL

// Motors need to be global variables since they need to be modified by interrupt functions
//Stepper baseMotor(200, 22, 23, 18, 60, 0, UINT32_MAX-1);
//DCPotMotor shoulderMotor(8, 9, A0, 0, 1023, 0, UINT32_MAX);
//Stepper elbowMotor(200, 4, 5, 2, 60, 0, UINT32_MAX-1);
Stepper wristPitchMotor(15652, 6, 7, 3, 60, 0, UINT32_MAX-1);
//DCMotor wristRollMotor(10, 11, 20, 19, 32, 374, 25, 0, UINT32_MAX);
//DCMotor fingersMotor(13, 12, 30, 21, 31, 374, 25, 0, UINT32_MAX-1);

/* // This function will be called by an interrupt
void updatePositionFingers() {
    fingersMotor.updatePosition();
}
void zeroFingers() {
// set encoderStepPosition to zero when the end stop is hit
// this function should be called from an interrupt
    fingersMotor.powerOff();
    fingersMotor.encoderStepPosition = 0;
} */

void zeroWristPitch() {
    wristPitchMotor.current_motor_radian = 0;
}

void setup(){
	init();
    SPI.begin();
	Serial.begin(9600);
	Serial.println("Initalized");
    delay(1000);

    /* // attach interupts for DC motors with encoders
    attachInterrupt(digitalPinToInterrupt(fingersMotor.encoderPinA), updatePositionFingers, RISING);
    attachInterrupt(digitalPinToInterrupt(fingersMotor.limitSwitchPin), zeroFingers, FALLING); */

    attachInterrupt(digitalPinToInterrupt(wristPitchMotor.limitSwitchPin), zeroWristPitch, FALLING);
}

int main(){
	setup();
    delay(1000);

    StepperAmis wristPitchMotorAmis(&wristPitchMotor, 5);

    wristPitchMotor.calibrate();
    //wristPitchMotor.rotateToRadian(UINT32_MAX / 2);
    wristPitchMotor.rotateToRadian(UINT32_MAX / 4);

	/* Arm testArm;
	uint32_t buffer[7];

    for(;;){
        // need to wait for serial data to be available?
        Serial.readBytes((char *)buffer, sizeof(uint32_t)*7); // not sure if this works

        Serial.println(buffer[1]);

        testArm.armTo(&buffer[1]);
    } */

	return 0;
}
