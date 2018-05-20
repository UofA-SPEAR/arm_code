//from https://howtomechatronics.com/tutorials/arduino/how-to-control-stepper-motor-with-a4988-driver-and-arduino/


const int stepPin = 3;
const int dirPin = 4;

/* Setup
pinMode(stepPin,OUTPUT);
pinMode(dirPin,OUTPUT);
*/

void fullRotation(){

  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 200; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(500);
  }

}
