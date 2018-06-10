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

    float upperBound;
    float lowerBound;
    int direction;
    unsigned long step_delay;
    int steps_per_rotation;
    int step_number;
    float radian_per_step;
    float current_motor_radian;
    int stepPin;
    int dirPin;
    unsigned long last_step_time;

};

#endif
