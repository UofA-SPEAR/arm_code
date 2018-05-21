//Copied from https://github.com/arduino/Arduino/blob/master/libraries/Stepper/src/Stepper.h


// ensure this library description is only included once
#ifndef StepperC_h
#define StepperC_h

// library interface description
class Stepper {
  public:
    // constructors:
    Stepper(int number_of_steps, int motor_pin_1, int motor_pin_2);

    // speed setter method:
    void setSpeed(long whatSpeed);

    // mover method:
    void step(int number_of_steps);

  private:
    void stepMotor(int rotationDelay);

    int direction;            // Direction of rotation
    unsigned long step_delay; // delay between steps, in ms, based on speed
    int number_of_steps;      // total number of steps this motor can take
    int pin_count;            // how many pins are in use.
    int step_number;          // which step the motor is on

    // motor pin numbers:
    int stepPin;
    int dirPin;

    unsigned long last_step_time; // time stamp in us of when the last step was taken
};

#endif
