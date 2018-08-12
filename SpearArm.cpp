#include "StepperC.h"
#include "SpearArm.h"
#include <Arduino.h>

Arm::Arm(){

  baseMotor = Stepper(15652, 22, 23, 2, 8000, 0, UINT32_MAX-1);
  shoulderMotor = DCPotMotor(8, 9, A0, 50, 110, 800);
  elbowMotor = Stepper(15652, 4, 5, 3, 8000, 0, UINT32_MAX/3);
  wristPitchMotor = Stepper(15652, 6, 7, 18, 2000, 0, UINT32_MAX-1);
  //wristRollMotor = DCMotor(10, 11, 21, 2, 374, 25, 0, UINT32_MAX);
  //fingersMotor = DCMotor(13, 12, 30, 3, 374, 25, 0, UINT32_MAX);

  shoulderMotor.setPIDParams(0.8, 0, 0, 1000/(THREAD_DURATION*NUM_MOTORS));

  Serial.println("motors init");
}

void Arm::home(){
// Moves all Stepper and DCMotor towards zero until they hit limit switch
// Moves DCPotMotor (shoulder) to a comfortable position
// DCPotMotor does not need a limit switch

  this->baseMotor.step_number = this->baseMotor.steps_per_rotation;
  this->elbowMotor.step_number = this->elbowMotor.steps_per_rotation;
  this->wristPitchMotor.step_number = this->wristPitchMotor.steps_per_rotation;

  while (this->baseMotor.step_number != 0
      || this->elbowMotor.step_number != 0
      /*|| this->wristPitchMotor.step_number != 0*/) {

    this->baseMotor.home();
    //this->shoulderMotor.home(); // moves shoulder to a comfortable position
    this->elbowMotor.home();
    //this->wristPitchMotor.home();
    // wrist roll has no limit switch
    //this->fingersMotor.home(); // add this back later

  }
}

void Arm::adjust(uint32_t *targets){
  /*
   * Moves each motor towards it's target radian for a short duration of time
   */

  this->baseMotor.rotateTowardsRadian(targets[BASE]);
  this->shoulderMotor.rotateTowardsRadian(targets[SHOULDER]);
  this->elbowMotor.rotateTowardsRadian(targets[ELBOW]);
  //this->wristPitchMotor.rotateTowardsRadian(targets[WRIST_PITCH]);
  this->wristRollMotor.rotateTowardsRadian(targets[WRIST_ROLL]);
  this->fingersMotor.rotateTowardsRadian(targets[FINGERS]);
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
