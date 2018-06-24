#include <Arduino.h>
#include "StepperC.h"
#include <string.h>
#include "SpearArm.h"

#include <math.h>

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
	for(float base = 0; base < 2*PI; base ++){
		Serial.println("-------new base-----");
		testMotor.rotateToRadian(base); //set to base angle

		//target angles and back
		for(int target = 1; target < 7; target++){
			testMotor.rotateToRadian(fmod(base + target, 2*PI));
			delay(200);
			testMotor.rotateToRadian(fmod(base,2*PI));
			delay(200);
		}

	}

	Serial.println("done");

}

void simple_arm_test(){
	Arm testArm;
	float targets[5] = {1,1,1,1,1};
	testArm.armTo(targets);
}

int main(){
	setup();

	Arm testArm;
	uint32_t buffer[7];

	// need to wait for serial data to be available?
	Serial.readBytes((char *)buffer, sizeof(uint32_t)*7); // not sure if this works

	double targets[5];
	for (i=0, i<5, i++) {
		// convert back to radians
		// bytes[0] should be the start signal
		// bytes[1] should be first byte of data
		targets[i] = (double) (buffer[i+1] / UINT32_MAX * M_PI * 2);
	}

	testArm.armTo((float)(targets));

	return 0;
}
