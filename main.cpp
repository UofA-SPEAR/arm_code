#include "SpearArm.h"
#include "StepperC.h"
#include "DCMotor.h"

#include <Arduino.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#define UINT32_MAX 4294967295UL

void setup(){
	init();
	Serial.begin(9600);
	Serial.println("Initalized");
}

void motor_test(){
	Serial.println("init stepper");
	Stepper testMotor(200, 3, 4, 0, 2*PI);

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

void simple_arm_test(){
	Arm testArm;
	uint32_t targets[5] = {3242341,23415,576575,52346,8784};
	testArm.armTo(targets);
}

void DCMotorTest() {
    DCMotor testMotor(8, 9, 0, UINT32_MAX);

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

int main(){
	setup();

    DCMotorTest();

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
