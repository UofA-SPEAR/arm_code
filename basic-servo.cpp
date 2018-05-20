//from https://howtomechatronics.com/tutorials/arduino/how-to-control-stepper-motor-with-a4988-driver-and-arduino/
// Stepper motor control using the A4988 Driver

const int stepPin = 3;
const int dirPin = 4;

const int stepsPerRevolution = 200
const int rotationSpeed = 500 // Good range: [300,4000]?

/* Setup
pinMode(stepPin,OUTPUT);
pinMode(dirPin,OUTPUT);
*/

void rotate(int numOfSteps, int direction = HIGH){
  /*
  Complete numOfSteps steps with the servo motor
  direction = HIGH or LOW (Default HIGH)
  */

  digitalWrite(dirPin,HIGH); //Set motor direction: [HIGH,LOW]
  for(int x = 0; x < numOfSteps; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(rotationSpeed);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(rotationSpeed);
  }

}
