#include "StepperC.h"
#include "SpearArm.h"
#include <Arduino.h>

//Constants for array index of each motor
#define BASE 0
#define SHOULDER 1
#define ELBOW 2
#define WRIST_PITCH 3
#define WRIST_ROLL 4
#define FINGERS 5
#define UINT32_MAX 4294967295UL

Arm::Arm(Motor** motors){
  this->motors = motors;

  //set motor speeds
  //this->BaseStepper->setSpeed(60);
  //this->ShoulderStepper->setSpeed(60);
  //this->ElbowStepper->setSpeed(60);
  //this->WristStepper->setSpeed(60);
  //this->FingerStepper->setSpeed(60);

}

void Arm::armTo(uint32_t *targets){
  /*
  params: array of floats of target radians for each motor
  will adjust each motor to target radians
  */

  this->motors[BASE]        ->rotateToRadian(targets[BASE]);
  this->motors[SHOULDER]    ->rotateToRadian(targets[SHOULDER]);
  this->motors[ELBOW]       ->rotateToRadian(targets[ELBOW]);
  this->motors[WRIST_PITCH] ->rotateToRadian(targets[WRIST_PITCH]);
  this->motors[WRIST_ROLL]  ->rotateToRadian(targets[WRIST_ROLL]);
  this->motors[FINGERS]     ->rotateToRadian(targets[FINGERS]);
}
