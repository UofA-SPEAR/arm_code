#include "StepperC.h"
#include "SpearArm.h"
#include <Arduino.h>

//R: remove and replace with a struct with one value per motor
//Constants for array index of each motor
#define BASE 0
#define SHOULDER 1
#define ELBOW 2
#define WRIST 3
#define FINGER 4

Arm::Arm(){
  /*
  Constructor
  */

  //R: do not use hardcoded pin numbers. define pin numbers as
  //   constants, and create a factory method for the default
  //   conficuration.


  //R: Arm has no destructor, so the stepper objects are
  //   never freed (XXX)

  //init motor objects
  this->BaseStepper = new Stepper(200, 3, 4, 0, 2*PI);
  this->ShoulderStepper = new Stepper(200, 5, 6, 0, 2*PI);
  this->ElbowStepper = new Stepper(200, 7, 8, 0, 2*PI);
  this->WristStepper = new Stepper(200, 9, 10, 0, 2*PI);
  this->FingerStepper = new Stepper(200, 11, 12, 0, 2*PI);

  //set motor speeds
  this->BaseStepper->setSpeed(60);
  this->ShoulderStepper->setSpeed(60);
  this->ElbowStepper->setSpeed(60);
  this->WristStepper->setSpeed(60);
  this->FingerStepper->setSpeed(60);

  //

}

void Arm::armTo(float *targets){
  /*
  params: array of floats of target radians for each motor
  will adjust each motor to target radians
  */

  this->BaseStepper->rotateToRadian(targets[BASE]);
  this->ShoulderStepper->rotateToRadian(targets[SHOULDER]);
  this->ElbowStepper->rotateToRadian(targets[ELBOW]);
  this->WristStepper->rotateToRadian(targets[WRIST]);
  this->FingerStepper->rotateToRadian(targets[FINGER]);
}
