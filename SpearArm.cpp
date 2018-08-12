#include "StepperC.h"
#include "SpearArm.h"
#include "common.h"

Arm::Arm(){

  baseMotor = Stepper(15652, 10, 11, 2, 8000, 0, UINT32_MAX-1);
  shoulderMotor = DCPotMotor(8, 9, A0, 50, 110, 800);
  elbowMotor = Stepper(15652, 4, 5, 3, 8000, 0, UINT32_MAX/3);
  wristPitchMotor = Stepper(15652, 6, 7, 18, 2000, 0, UINT32_MAX-1);

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
  Serial.println("Wrist start");
  this->wristPitchMotor.rotateTowardsRadian(targets[WRIST_PITCH]);
  Serial.println("Wrist end");
}
