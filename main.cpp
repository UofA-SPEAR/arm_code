#include "SpearArm.h"
#include "StepperC.h"
#include "Motor.h"
#include "DCMotor.h"
#include "DCPotMotor.h"

#include <Arduino.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#define UINT32_MAX 4294967295UL

// DCMotors need to be global variables since they need to be accessed by an interrupt function
DCMotor fingersMotor(8, 9, 3, 2, 4, 374, 25, 0, 3 * (UINT32_MAX/4));

// This function will be called by an interrupt
void updatePositionFingers() {
    fingersMotor.updatePosition();
}
void zeroFingers() {
// set encoderStepPosition to zero when the end stop is hit
// this function should be called from an interrupt
    fingersMotor.powerOff();
    fingersMotor.encoderStepPosition = 0;
}

void setup(){
	init();
	Serial.begin(9600);
    pinMode(13, OUTPUT);
	Serial.println("Initalized");
    delay(1000);

    // attach interupts for DC motors with encoders
    attachInterrupt(digitalPinToInterrupt(fingersMotor.encoderPinA), updatePositionFingers, RISING);
    attachInterrupt(digitalPinToInterrupt(fingersMotor.limitSwitchPin), zeroFingers, FALLING);
}

void motor_test(){
	Serial.println("init stepper");
	Stepper testMotor(200, 3, 4, 5, 60, 0, UINT32_MAX);

	Serial.println("setting rotation speed");
	testMotor.setSpeed(120);


	//full angle test
    uint32_t increment = 100000000;
	for(uint32_t base = increment; base >= increment; base += increment){
		Serial.println("-------new base-----");
		Serial.println(base);
		Serial.println("--------------------");
		testMotor.rotateToRadian(base); //set to base angle
        delay(100);
	}

	Serial.println("done");

}

void DCMotorSimpleTest() {
    DCMotor testMotor(8, 9, 3, 2, 4, 374, 25, 0, UINT32_MAX);

    Serial.println("-----Beginning DC Motor Test-----");
    testMotor.powerOn(true, 25);
    delay(1001);
    testMotor.powerOff();
    delay(1001);
    testMotor.powerOn(false, 25);
    delay(1001);
    testMotor.powerOff();
    Serial.println("-----End DC Motor Test-----");
}

void encoderTest() {

    Serial.println("Beginning Encoder Test");

    fingersMotor.powerOn(true, 25);
    while (abs(fingersMotor.encoderStepPosition) < fingersMotor.pulsesPerRevolution) {
        Serial.println(fingersMotor.current_motor_radian);
        Serial.println("---");
        Serial.println(digitalRead(fingersMotor.encoderPinB));
    }
    fingersMotor.powerOff();
    delay(1000);
    
    fingersMotor.powerOn(false, 25);
    while (fingersMotor.encoderStepPosition != 0) {
        Serial.println(fingersMotor.encoderStepPosition);
    }
    fingersMotor.powerOff();
}

void DCAngleTest () {
//full angle test for DCMotor
//there are some integer overflow errors here

    int basesCount = 4;
    uint32_t base = UINT32_MAX / basesCount;
    int targetsCount = 8;
    uint32_t target = UINT32_MAX / targetsCount;
	for(int i = 0; i < basesCount; i++){
        base = base + i * (UINT32_MAX / basesCount);
		Serial.println("-------new base-----");
		Serial.println(base);
		Serial.println("--------------------");
		fingersMotor.rotateToRadian(base); //set to base angle
        delay(1000);
        
        //target angles and back
        for(int j = 0; j < targetsCount; j++){
            target = target + j * (UINT32_MAX / targetsCount);
            Serial.println((uint32_t)(base+target));
            fingersMotor.rotateToRadian(base + target);
            delay(500);
            fingersMotor.rotateToRadian(base);
            delay(500);
        }
	}

	Serial.println("done");
}

int main(){
	setup();
    delay(1000);

    fingersMotor.calibrate();
    delay(1000);
    fingersMotor.rotateToRadian(UINT32_MAX / 2);

    //while (1) {
        //Serial.println(fingersMotor.encoderStepPosition);
    //}
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
