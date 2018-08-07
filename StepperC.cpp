//sourced from https://github.com/arduino/Arduino/blob/master/libraries/Stepper/src/Stepper.cpp

#include "Arduino.h"
#include "StepperC.h"
#include <math.h>
#include <stdint.h>

Stepper::Stepper(uint32_t steps_per_rotation, int stepPin, int dirPin, int limitSwitchPin, long RPM, uint32_t lowerBound, uint32_t upperBound){
  /*
  Constructor: 2-pin Stepper motor constructor with A4988 Driver module.
  */

  this->step_number = 0; // which step the motor is on
  this->direction = HIGH;
  this->last_step_time = 0;
  this->steps_per_rotation = steps_per_rotation; //# of steps for 1 rotation
  this->stepPin = stepPin;
  this->dirPin = dirPin;
  this->limitSwitchPin = limitSwitchPin;
  this->radian_per_step = UINT32_MAX  / steps_per_rotation;
  this->current_motor_radian = 0;
  this->upperBound = upperBound;
  this->lowerBound = lowerBound;

  //setup the pins on the microcontroller:
  pinMode(this->stepPin, OUTPUT);
  pinMode(this->dirPin, OUTPUT);
  pinMode(this->limitSwitchPin, INPUT_PULLUP);
  digitalWrite(this->stepPin, LOW);
  digitalWrite(this->dirPin, this->direction);

  //set speed in RPM
  this->setSpeed(RPM);

  // set forwardDirection to HIGH by default
  this->setForwardDirection(true);
}


void Stepper::rotateToRadian(uint32_t target_radian){
  /*
  given target radian rotate to that value using a calculated number of steps
  */
  //constrain to motor bounds
  target_radian = constrain(target_radian, lowerBound, upperBound);
  int64_t diff = (target_radian - this->current_motor_radian);

  //calculate minimum difference to target angle
  //only do this optimization if the motor can rotate the full 360 degrees
  if(this->lowerBound == 0 && this->upperBound == UINT32_MAX) {
    if(diff > UINT32_MAX/2){
      diff = diff - UINT32_MAX;
    }
    if(diff < -1*(UINT32_MAX/2)){
      diff = abs(UINT32_MAX - abs(diff));
    }
  }

  //convert difference radian to number of steps and execute # steps
  int64_t required_steps = diff / radian_per_step;

  this->step(required_steps);
  this->current_motor_radian = target_radian;
}


void Stepper::setSpeed(long RPM){
  /*
  Sets the speed in revs per minute
  */
  this->step_delay = 60L * 1000L * 1000L / this->steps_per_rotation / RPM;
}


void Stepper::step(int64_t steps_to_move){
  /*
   * Moves the motor [steps_to_move] steps.  If the number is negative,
   * the motor moves in the reverse direction.
   */

  // reverse the direction if this->forwardDirection is set to LOW
  if (this->forwardDirection == LOW) {
    steps_to_move = -1 * steps_to_move;
  }

  int64_t steps_left = abs(steps_to_move);  // how many steps to take

  // determine direction based on whether steps_to_mode is + or -:
  if (steps_to_move > 0){
    this->direction = HIGH;
    digitalWrite(this->dirPin, direction);
  }
  if (steps_to_move < 0){
    this->direction = LOW;
    digitalWrite(this->dirPin, direction);
   }

  // decrement the number of steps, moving one step each time:
  while (steps_left > 0){
    unsigned long now = micros(); // MIGHT >1 hour running problem?

    // It is important that this subtraction is done in
    // an assignment to an unsigned variable
    unsigned long diff = now - this->last_step_time;

    // move only if the appropriate delay has passed:
    if (diff >= this->step_delay){
      // get the timeStamp of when you stepped:
      this->last_step_time = now;
      // increment or decrement the step number,
      // depending on direction:
      if (this->direction == HIGH){
        this->step_number++;
        if (this->step_number == this->steps_per_rotation) {
          this->step_number = 0;
        }
      }else{
        if (this->step_number == LOW) { //nooooot the right variable
          this->step_number = this->steps_per_rotation;
        }
        this->step_number--;
      }
      // decrement the steps left:
      steps_left--;
      //Cause pulse of stepper motor
      stepMotor((unsigned long)(this->step_delay / 2));
    }
  }
}


void Stepper::stepMotor(int rotationDelay){
  /*
  Steps the motor by a single step, runtime: 2*rotationDelay
  */
  digitalWrite(stepPin,HIGH);
  delayMicroseconds(rotationDelay);
  digitalWrite(stepPin,LOW);
  delayMicroseconds(rotationDelay);

  // TODO: don't hard code this delay
  delayMicroseconds(2000);
}

void Stepper::calibrate() {
  // moves motor in false direction until interrupted by limit switch
  // this function should be called in an interrupt
  // the interrupt function should set current_motor_radian to lowerBound when the limit switch is triggered

  // check to see if limit switch is already triggered
  if (digitalRead(this->limitSwitchPin) == LOW) {
    this->current_motor_radian = 0;
    return;
  }

  this->current_motor_radian = this->upperBound;
  while (this->current_motor_radian > this->lowerBound) {
    this->step(-1);
  }
  this->current_motor_radian = lowerBound;
}
