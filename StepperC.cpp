//copied from https://github.com/arduino/Arduino/blob/master/libraries/Stepper/src/Stepper.cpp
//TODO: Modify for A4988 Driver compatability and radian mode

#include "Arduino.h"
#include "StepperC.h"

Stepper::Stepper(int number_of_steps, int stepPin, int dirPin){
  /*
  * two-wire constructor.
  * Sets which wires should control the motor.
  */
  this->step_number = 0;     // which step the motor is on
  this->direction = HIGH;    // motor direction
  this->last_step_time = 0;  // time stamp in us of the last step taken
  this->number_of_steps = number_of_steps; // total number of steps for this motor

  // Arduino pins for the motor control connection:
  this->stepPin = stepPin;
  this->dirPin = dirPin;

  // setup the pins on the microcontroller:
  pinMode(this->stepPin, OUTPUT);
  pinMode(this->dirPin, OUTPUT);
  digitalWrite(this->dirPin, this->direction); //MIGHT NOT BE FORMATTED CORRECT?
}


void Stepper::setSpeed(long whatSpeed){
  /*
   * Sets the speed in revs per minute
   */
  this->step_delay = 60L * 1000L * 1000L / this->number_of_steps / whatSpeed;
}


void Stepper::step(int steps_to_move){
  /*
   * Moves the motor steps_to_move steps.  If the number is negative,
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
    unsigned long now = micros(); // MIGHT >1 hour running problem??
    // move only if the appropriate delay has passed:
    if (now - this->last_step_time >= this->step_delay){
      // get the timeStamp of when you stepped:
      this->last_step_time = now;
      // increment or decrement the step number,
      // depending on direction:
      if (this->direction == HIGH){
        this->step_number++;
        if (this->step_number == this->number_of_steps) {
          this->step_number = 0;
        }
      }else{
        if (this->step_number == LOW) {
          this->step_number = this->number_of_steps;
        }
        this->step_number--;
      }
      // decrement the steps left:
      steps_left--;

      //Cause pulse of stepper motor
      //intended runtime of stepMotor is one step_delay
      stepMotor((unsigned long)(this->step_delay / 2));  //TIME NOT CORRECT?
    }
  }
}


void Stepper::stepMotor(int rotationDelay){
  /*
  Steps the motor by a single step
  rotationDelay [300,4000] from example
  */
  digitalWrite(stepPin,HIGH); //apparently 2 microseconds?
  delayMicroseconds(rotationDelay);
  digitalWrite(stepPin,LOW);
  delayMicroseconds(rotationDelay);
}
