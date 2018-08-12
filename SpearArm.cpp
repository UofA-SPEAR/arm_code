#include "StepperC.h"
#include "SpearArm.h"
#include "common.h"
#include "main.h"

Arm::Arm(){

  baseMotor = Stepper(15652, 10, 11, 2, 8000, 0, UINT32_MAX-1);
  shoulderMotor = DCPotMotor(8, 9, A0, 50, 110, 800);
  elbowMotor = Stepper(15652, 4, 5, 3, 8000, 0, UINT32_MAX/3);
  wristPitchMotor = Stepper(15652, 6, 7, 18, 2000, 0, UINT32_MAX-1);

  shoulderMotor.setPIDParams(0.8, 0, 0, 1000/(THREAD_DURATION*2));

  Serial.println("motors init");
}

void Arm::home(){
// Moves all Stepper and DCMotor towards zero until they hit limit switch
// Moves DCPotMotor (shoulder) to a comfortable position
// DCPotMotor does not need a limit switch

  this->baseMotor.step_number = this->baseMotor.steps_per_rotation;
  this->elbowMotor.step_number = this->elbowMotor.steps_per_rotation;
  this->wristPitchMotor.step_number = this->wristPitchMotor.steps_per_rotation;

  in_home_mode = true;
  while (this->baseMotor.step_number != 0) {
    this->baseMotor.home();
  }

  while (this->elbowMotor.step_number != 0) {
    this->elbowMotor.home();
  }

  in_home_mode = false;

}

void Arm::adjust(uint32_t *targets){
  /*
   * Moves each motor towards it's target radian for a short duration of time
   */

  this->baseMotor.rotateTowardsRadian(targets[BASE]);
  this->shoulderMotor.rotateTowardsRadian(targets[SHOULDER]);
  //this->elbowMotor.rotateTowardsRadian(targets[ELBOW]);
}
