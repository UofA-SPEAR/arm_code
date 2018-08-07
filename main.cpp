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

// This function will be called by an interrupt
void updatePositionFingers() {
    arm->fingersMotor.updatePosition();
}
void zeroFingers() {
// set encoderStepPosition to zero when the end stop is hit
// this function should be called from an interrupt
    arm->fingersMotor.powerOff();
    arm->fingersMotor.encoderStepPosition = 0;
}

void zeroElbow() {
    arm->elbowMotor.current_motor_radian = 0;
}

void setup(){
	init();
    SPI.begin();
	Serial.begin(9600);
	Serial.println("Initalized");
    delay(1000);
	Serial.println("Delayed");

    // attach interupts for DC motors with encoders
    attachInterrupt(digitalPinToInterrupt(arm->fingersMotor.encoderPinA), updatePositionFingers, RISING);
    attachInterrupt(digitalPinToInterrupt(arm->fingersMotor.limitSwitchPin), zeroFingers, FALLING);

    attachInterrupt(digitalPinToInterrupt(arm->elbowMotor.limitSwitchPin), zeroElbow, FALLING);
}

int main(){
	setup();
    Serial.println("after setup");
    arm = new Arm();
    Serial.println("started");

    // initialize steppers that use the amis driver
    StepperAmis elbowMotorAmis(42, 2000);

    arm->elbowMotor.step(2000);
    arm->elbowMotor.step(-2000);

	/*uint32_t buffer[6];
    for(;;){
        Serial.println(":(");
        if (Serial.available() >= 24) {
            Serial.println("in Loop");
            Serial.readBytes((char *)buffer, sizeof(uint32_t)*6); // not sure if this works
            Serial.println(buffer[0]);
            arm->armTo(&buffer[0]);
            Serial.println("after armTo");
        }else{
            Serial.println("else");
        }
    }*/

	return 0;
}
