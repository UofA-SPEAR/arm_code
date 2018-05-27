#include <Arduino.h>
#include "StepperC.h"
#include <string.h>

void setup(){
	init();
	Serial.begin(9600);
	Serial.println("Initalized");

}

int main(){
	setup();

	Serial.println("init stepper");
	int r = 200;
	Stepper testMotor(r, 3, 4);

	Serial.println("setting rotation speed");
	testMotor.setSpeed(30);

	Serial.println("stepping full rotation");
	testMotor.step(r);

	Serial.println("rotate to 1");
	testMotor.rotateToRadian(1);

	Serial.println("rotate to 2");
	testMotor.rotateToRadian(2);

	Serial.println("rotate to 1");
	testMotor.rotateToRadian(1);


	return 0;
}
