//Origin from https://github.com/arduino/Arduino/blob/master/libraries/Stepper/src/Stepper.h

#ifndef StepperC_h
#define StepperC_h

class Stepper {

  public:
    Stepper(int number_of_steps, int stepPin, int dirPin, float lowerBound, float upperBound);
    void setSpeed(long RPM);
    void step(int number_of_steps);
    void rotateToRadian(float target_radian);

    void stepMotor(int rotationDelay);

    //R: many of these can probably be private
    float upperBound;
    float lowerBound;
    int direction; //R: does not need to be a class variable, only used in step
    unsigned long step_delay;
    int steps_per_rotation;
    int step_number;
    //R: radian_per_step and current_motor_radian serve
    //   no purpose, as the can be calculated from
    //   steps_per_rotation and step_number, and provide
    //   less accuracy for calculations
    float radian_per_step;
    float current_motor_radian;
    int stepPin;
    int dirPin;
    unsigned long last_step_time;

};

#endif
