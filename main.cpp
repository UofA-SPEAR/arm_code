#include "SpearArm.h"
#include "StepperC.h"
#include "DCMotor.h"

#include <Arduino.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#define UINT32_MAX 4294967295UL

// DCMotors need to be global variables since they need to be accessed by an interrupt function
volatile DCMotor shoulderMotor(8, 9, 2, 4, 374, 0, 3 * (UINT32_MAX/4));

// This function will be called by an interrupt
void updatePositionFingers() {
    shoulderMotor.updatePosition();
}

void setup(){
	init();
	Serial.begin(9600);
	Serial.println("Initalized");
    delay(1000);

    // attach interupts for DC motors with encoders
    attachInterrupt(digitalPinToInterrupt(shoulderMotor.encoderPinA), updatePositionFingers, RISING);
}

void torqueTest() {
    for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
        Serial.println(dutyCycle);
        shoulderMotor.powerOn(true, dutyCycle);
        delay(1000);
    }
}

int main(){
	setup();

    torqueTest();

    return 0;
}
