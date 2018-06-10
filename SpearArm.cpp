#include "StepperC.h"
#include "SpearArm.h"



Arm::Arm(){
  /*
  Constructor
  */

  //init motor objects
  this->BaseStepper = new Stepper(200, 3, 4);
  this->ShoulderStepper = new Stepper(200, 5, 6);
  this->ElbowStepper = new Stepper(200, 7, 8);
  this->WristStepper = new Stepper(200, 9, 10);
  this->FingerStepper = new Stepper(200, 11, 12);

  //set motor speeds
  this->BaseStepper->setSpeed(60);
  this->ShoulderStepper->setSpeed(60);
  this->ElbowStepper->setSpeed(60);
  this->WristStepper->setSpeed(60);
  this->FingerStepper->setSpeed(60);

  //

}

void Arm::armTo(){
  /*
  params: array of floats of target radians for each motor
  will adjust each motor to target radians
  */

}
