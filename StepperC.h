//Origin from https://github.com/arduino/Arduino/blob/master/libraries/Stepper/src/Stepper.h

#ifndef StepperC_h
#define StepperC_h

class Stepper {

  public:
    Stepper(int number_of_steps, int stepPin, int dirPin);
    void setSpeed(long whatSpeed);
    void step(int number_of_steps);
    void rotateToRadian(float target_radian);

  private:
    void stepMotor(int rotationDelay);

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
