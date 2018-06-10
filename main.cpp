#include <Arduino.h>
#include "StepperC.h"
#include <string.h>
#include "SpearArm.h"

void setup(){
	init();
	Serial.begin(9600);
	Serial.println("Initalized");

}

void motorTest(){
	Serial.println("init stepper");
	Stepper testMotor(200, 3, 4);

	Serial.println("setting rotation speed");
	testMotor.setSpeed(60);


	//full angle test
	for(float base = 0; base < 2*PI; base ++){
		Serial.println("-------new base-----");
		testMotor.rotateToRadian(base); //set to base angle

		//target angles and back
		for(int target = 1; target < 7; target++){
			testMotor.rotateToRadian(base + target);
			delay(500);
			testMotor.rotateToRadian(base);
			delay(500);
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
