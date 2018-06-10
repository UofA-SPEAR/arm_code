//sourced from https://github.com/arduino/Arduino/blob/master/libraries/Stepper/src/Stepper.cpp

#include "Arduino.h"
#include "StepperC.h"
#include <math.h>


Stepper::Stepper(int steps_per_rotation, int stepPin, int dirPin, float upperBound, float lowerBound){
  /*
  Constructor: 2-pin Stepper motor constructor with A4988 Driver module.
  */

  this->step_number = 0; // which step the motor is on
  this->direction = HIGH;
  this->last_step_time = 0;
  this->steps_per_rotation = steps_per_rotation; //# of steps for 1 rotation
  this->stepPin = stepPin;
  this->dirPin = dirPin;
  this->radian_per_step = (2 * PI) / steps_per_rotation;
  this->current_motor_radian = 0; //How do you know position 0?
  this->upperBound = upperBound;
  this->lowerBound = lowerBound;

  //setup the pins on the microcontroller:
  pinMode(this->stepPin, OUTPUT);
  pinMode(this->dirPin, OUTPUT);
  digitalWrite(this->dirPin, this->direction);
}


void Stepper::rotateToRadian(float target_radian){
  /*
  given target radian rotate to that value using a calculated number of steps
  */
  //constrain to motor bounds
  target_radian = constrain(target_radian, lowerBound, upperBound);
  float diff = (target_radian - this->current_motor_radian);
  //calculate minimum difference to target angle
  if(diff > PI){
      diff = diff - 2*PI;
  }
  if(diff < -1*PI){
    diff = abs(2*PI - abs(diff));

  }
  //convert difference radian to number of steps and execute # steps 
  int required_steps = diff * (1/radian_per_step);
  step(required_steps);
  this->current_motor_radian = fmod(target_radian, (2*PI));
}


void Stepper::setSpeed(long RPM){
  /*
  Sets the speed in revs per minute
  */
  this->step_delay = 60L * 1000L * 1000L / this->steps_per_rotation / RPM;
}


void Stepper::step(int steps_to_move){
  /*
   * Moves the motor [steps_to_move] steps.  If the number is negative,
   * the motor moves in the reverse direction.
   */
  int steps_left = abs(steps_to_move);  // how many steps to take

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
    // move only if the appropriate delay has passed:
    if (now - this->last_step_time >= this->step_delay){
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
}
