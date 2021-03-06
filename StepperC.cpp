//sourced from https://github.com/arduino/Arduino/blob/master/libraries/Stepper/src/Stepper.cpp

#include "common.h"
#include "StepperC.h"
#include <math.h>
#include <stdint.h>
#include "main.h"

Stepper::Stepper(uint32_t steps_per_rotation, int stepPin, int dirPin, int limitSwitchPin, uint32_t stepDelay, uint32_t lowerBound, uint32_t upperBound){
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
  this->stepDelay = stepDelay;
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

  // set forwardDirection to HIGH by default
  this->setForwardDirection(true);
}

void Stepper::rotateTowardsRadian(uint32_t target_radian) {
    // for 10 milliseconds or less, moves motor towards target_radian

    // get the start time
    uint32_t startTime = millis(); // timer will overflow after about 50 days

    // calculate target step number
    target_radian = constrain(target_radian, lowerBound, upperBound);
    uint32_t target_step_number = ((double)target_radian) / ((double)radian_per_step); 

    // calculate the optimal path towards the target position
    int64_t diff = ((int64_t)target_step_number) - ((int64_t)this->step_number);

    // determine direction
    int dir;
    if (diff > 0) {
        dir = this->forwardDirection;
    } else {
        dir = this->reverseDirection;
    }

    digitalWrite(this->dirPin, dir);
    Serial.println(dir);
    delayMicroseconds(5); // needed so direction pin has time to init

    if (stepper_hold != 42) {
        if (!in_home_mode) {
            return;
        }
    }

    stepper_hold = 1;

    // move the motor and update step_number
    while(millis() - startTime < THREAD_DURATION) {
        if (this->step_number != target_step_number){
            this->stepMotor(this->stepDelay);
            if (dir == this->forwardDirection) {
                if (this->step_number == this->steps_per_rotation) {
                    this->step_number = 0;
                } else {
                    this->step_number++;
                }
            } else {
                if (this->step_number == 0) {
                    this->step_number = this->steps_per_rotation;
                } else {
                    this->step_number--;
                }
            }
        }
    }
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

  if (required_steps < 0) {
    delay(1000);
  } else {
    delay(1000);
  }

  this->step(required_steps);
  this->current_motor_radian = target_radian;
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
      // decrement the steps left:
      steps_left--;
      //Cause pulse of stepper motor
      stepMotor(this->stepDelay);
  }
}


void Stepper::stepMotor(uint32_t stepDelay){
  /*
  Steps the motor by a single step
  */
  digitalWrite(stepPin,HIGH);
  delayMicroseconds(4);
  digitalWrite(stepPin,LOW);

  delayMicroseconds(2000);
}

void Stepper::home() {
  // moves motor in false direction until interrupted by limit switch
  // this function should be called in an interrupt
  // the interrupt function should set current_motor_radian to lowerBound when the limit switch is triggered


  if (digitalRead(this->limitSwitchPin) == LOW) {
    this->step_number = 0;
    return;
  }


  //this->step_number = this->steps_per_rotation;
  this->rotateTowardsRadian(0);

}
