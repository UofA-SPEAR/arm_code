Arm Code Overview
=================

Basics
-----------
Stepper motors are controlled by A4988 Driver.
StepperC (stepper custom) is source code from the original Arduino Stepper library. StepperC is to be re-written with the assumption that stepper motors are being controlled by the A4988 Driver. The stepper class will have functions to allow for radian control of motors.

Plan
--------
- each motor has a range of angles it could attain
  - How will the zero angles be set?  
- input from Ros will be a new set of stepper motor angles
  - new angles will be compared to existing angles
  - steps will be taken to adjust the angles of each motor

Arm class
----------
- list of angles
- stepper vairables (ex. steps per revolotion)

- adjustment calculator

- base stepper
- elbow stepper
- wrist stepper

- elbow (DC motor)
