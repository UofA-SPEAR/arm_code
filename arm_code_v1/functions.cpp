#include <Arduino.h>
#include "header.h"
#include <Servo.h>


//creating servo classes 
Servo base;
Servo elbow;
Servo shoulder;
int ANGLELBOW = 1500;
int ANGLESHOULDER = 650;
// int ANGLEBASE = 1500;

int SPEED = 10;
bool microMode = true;

void setup() {
	init();

  Serial.begin(9600);

  // m
  //defining servo class values
  base.attach(8);
  shoulder.attach(9);
  elbow.attach(10);
  base.write(88);

  Serial.println("Starting up...");
  Serial.println("Elbow: W/S");
  Serial.println("Shoulder: A/D");
  Serial.println("Base: Q/E");

  delay(10);
}

char receiveChar(){
  char signal = 0;
  if(Serial.available() > 0){
    signal = Serial.read();
  }
  
  Serial.flush();

  return signal; 
}

void changeMode(){
  if(microMode){
    SPEED = 3;
    microMode = !microMode;
    Serial.println("Micro Mode Engaged");
  }
  else{
    SPEED = 12;
    microMode = !microMode;
    Serial.println("Standard Mode Engaged");
  }
}


void servo(){
  //todo: replace analog with ros imputs


  char signal = receiveChar();

  
  ANGLESHOULDER = constrain(ANGLESHOULDER,100,1100);
  ANGLELBOW = constrain(ANGLELBOW,1000,2000);
  // ANGLEBASE = constrain(ANGLEBASE,400,800);


  //conditionals to check right joystick 
  if(signal== 'a'){
    //if the joystick is moved up
      ANGLESHOULDER +=5;
      shoulder.writeMicroseconds(ANGLESHOULDER);
    
  }
  else if (signal== 'd'){
    //if the joystick is moved down
      ANGLESHOULDER -=5;
      shoulder.writeMicroseconds(ANGLESHOULDER);
  }

  //conditionals to check left joystick
  if(signal== 'w'){
    //if the joystick is moved up
      ANGLELBOW += SPEED;
      elbow.writeMicroseconds(ANGLELBOW);
  }
  else if (signal== 's'){
    //if the joystick is moved down
      ANGLELBOW -= SPEED;
      elbow.writeMicroseconds(ANGLELBOW);
  }



  //conditionals to check buttons for base servo
  if(signal== 'q'){
    //inditactes the left button has been pressed
    // ANGLEBASE += SPEED;
    // base.writeMicroseconds(ANGLEBASE);
    base.write(84);
    
  }
  else if (signal == 'e'){
    //indicatees the right button has been pressed
      // ANGLEBASE -= SPEED;
      // base.writeMicroseconds(ANGLEBASE);
    base.write(92);
  }
  else if(signal == 'r'){
    base.write(88);
  }
  
  
  if(signal == 'x'){
    changeMode();
  }



}




// ros shit

// #include <Arduino.h>
// #include "header.h"
// #include <ros.h>
// #include <std_msgs/String.h>


// ros::NodeHandle nh;

// std_msgs:: String str_msg;

// ros::Subscriber<std_msgs::Empty> sub("receive_req", &messageCb );


//  nh.initNode();
// nh.subscribe(sub);


