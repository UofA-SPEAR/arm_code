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

void motorTest(){
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

int main(){
	setup();

	Arm testArm;
	testArm.armTo();

	return 0;
}
