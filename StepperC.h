//Origin from https://github.com/arduino/Arduino/blob/master/libraries/Stepper/src/Stepper.h

#ifndef StepperC_h
#define StepperC_h
#include <stdint.h>

class Stepper {

  public:
    Stepper(int number_of_steps, int stepPin, int dirPin, int limitSwitchPin, long RPM, uint32_t lowerBound, uint32_t upperBound);
    void setSpeed(long RPM);
    void step(int number_of_steps);
    void rotateToRadian(uint32_t target_radian);
    void stepMotor(int rotationDelay);
    void calibrate();

    uint32_t upperBound;
    uint32_t lowerBound;
    int direction;
    unsigned long step_delay;
    int steps_per_rotation;
    int step_number;
    uint32_t radian_per_step;
    uint32_t current_motor_radian;
    int stepPin;
    int dirPin;
    int limitSwitchPin;
    unsigned long last_step_time;

};

#endif
