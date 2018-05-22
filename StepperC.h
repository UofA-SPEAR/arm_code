//Copied from https://github.com/arduino/Arduino/blob/master/libraries/Stepper/src/Stepper.h


// ensure this library description is only included once
#ifndef StepperC_h
#define StepperC_h

// library interface description
class Stepper {
  public:
    // constructors:
    Stepper(int number_of_steps, int stepPin, int dirPin);

    // speed setter method:
    void setSpeed(long whatSpeed);

    // mover method:
    void step(int number_of_steps);

    // move to radian method:
    void rotateToRadian(float target_radian);

  private:
    void stepMotor(int rotationDelay);

    int direction;            // Direction of rotation
    unsigned long step_delay; // delay between steps, in ms, based on speed
    int steps_per_rotation;   // # of steps in one rotation of motor
    int pin_count;            // how many pins are in use.
    int step_number;          // which step the motor is on

    float radian_per_step;    // used to calculate required steps
    float current_motor_radian;// current motor angle

    // motor pin numbers:
    int stepPin;
    int dirPin;

    unsigned long last_step_time; // time stamp in us of when the last step was taken
};

#endif
