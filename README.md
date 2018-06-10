Arm Code Overview
=================

Basics
-----------
Stepper motors are controlled by A4988 Driver.
StepperC (stepper custom) is source code from the original Arduino Stepper library. StepperC is to be re-written with the assumption that stepper motors are being controlled by the A4988 Driver. The stepper class will have functions to allow for radian control of motors.


motor class
-----------
- top and bottom bounds for radian
- polymorph to allow DC motor
- when given an angle, motors perform all required calculations to get there


Arm class
----------
- 5 instances of motor class
  - base stepper
  - elbow stepper
  - wrist stepper
  - etc
- write armTo function, considering bounds


Possible Problems
------------------
- stepper code might not work after an hour (micros() max value)
- only one motor will move at a time
- delay into step motor might not be correct?
