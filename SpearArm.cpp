#include "StepperC.h"
#include "SpearArm.h"



Arm::Arm(){
  /*
  Constructor
  */

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
