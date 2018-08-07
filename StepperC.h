//Origin from https://github.com/arduino/Arduino/blob/master/libraries/Stepper/src/Stepper.h

#ifndef StepperC_h
#define StepperC_h

#include "Motor.h"

#include <stdint.h>

class Stepper: public Motor {

  public:
    Stepper() {}
    Stepper(uint32_t steps_per_rotation, int stepPin, int dirPin, int limitSwitchPin, long RPM, uint32_t lowerBound, uint32_t upperBound);
    void setSpeed(long RPM);
    void step(int64_t number_of_steps);
    void rotateToRadian(uint32_t target_radian);
    void stepMotor(int rotationDelay);
    void calibrate();

    unsigned long step_delay;
    uint32_t steps_per_rotation;
    int step_number;
    uint32_t radian_per_step;
    int stepPin;
    int dirPin;
    int limitSwitchPin;
    unsigned long last_step_time;

};

#endif
