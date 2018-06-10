#include "StepperC.h"
#include "SpearArm.h"



Arm::Arm(){
  /*
  Constructor
  */

  //init motor objects
  this->BaseStepper = Stepper BaseStepper(200, 3, 4);
  this->ShoulderStepper = Stepper ShoulderStepper(200, 5, 6);
  this->ElbowStepper = Stepper ElbowStepper(200, 7, 8);
  this->WristStepper = Stepper WristStepper(200, 9, 10);
  this->FingerStepper = Stepper FingerStepper(200, 11, 12);

  //set motor speeds
  this->BaseStepper.setSpeed(60);
  this->ShoulderStepper.setSpeed(60);
  this->ElbowStepper.setSpeed(60);
  this->WristStepper.setSpeed(60);
  this->FingerStepper.setSpeed(60);

  //

}

void Arm::armTo(){
  /*
  params: array of floats of target radians for each motor
  will adjust each motor to target radians
  */

}

void Arm::setAllZeros(){
  /*
  calibration function to overwrite zero angle for all motors
  */
  this->BaseStepper.current_motor_radian = 0;
  this->ShoulderStepper.current_motor_radian = 0;
  this->ElbowStepper.current_motor_radian = 0;
  this->WristStepper.current_motor_radian = 0;
  this->FingerStepper.current_motor_radian = 0;
}
