Arm Code Overview
=================

Plan
--------
- each motor has a range of angles it could attain
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
