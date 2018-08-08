#include "StepperC.h"
#include "SpearArm.h"
#include <Arduino.h>

Arm::Arm(){

  baseMotor = Stepper(200, 22, 23, 18, 2000, 0, UINT32_MAX-1);
  shoulderMotor = DCPotMotor(8, 9, A0, 0, 1023, 0, UINT32_MAX);
  elbowMotor = Stepper(15652, 4, 5, 2, 8000, 0, UINT32_MAX/2);
  wristPitchMotor = Stepper(15652, 6, 7, 3, 2000, 0, UINT32_MAX-1);
  wristRollMotor = DCMotor(10, 11, 20, 19, 32, 374, 25, 0, UINT32_MAX);
  fingersMotor = DCMotor(13, 12, 30, 21, 31, 374, 25, 0, UINT32_MAX-1);

  Serial.println("motors init");
}

void Arm::armTo(uint32_t *targets){
  /*
  params: array of floats of target radians for each motor
  will adjust each motor to target radians
  */

  this->baseMotor.rotateToRadian(targets[BASE]);
  this->shoulderMotor.rotateToRadian(targets[SHOULDER]);
  this->elbowMotor.rotateToRadian(targets[ELBOW]);
  this->wristPitchMotor.rotateToRadian(targets[WRIST_PITCH]);
  this->wristRollMotor.rotateToRadian(targets[WRIST_ROLL]);
  this->fingersMotor.rotateToRadian(targets[FINGERS]);
}
