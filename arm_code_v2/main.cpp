#include <Arduino.h>
#include <Stepper.h>
#include <string.h>


//Constants
#define BASE 0
#define SHOULDER 1
#define ELBOW 2
#define WRIST 3
#define CLAW 5

class Arm{
	
	public:
		int arm_num, arm_step;
		int stepsPerRevolution;
		Arm();
		void write_stepper(int stepper_num);
	private:
		Stepper base_stepper;
		Stepper elbow_stepper;
		Stepper shoulder_stepper;
		Stepper wrist_stepper;

};

Arm::Arm():
	stepsPerRevolution(64),
	base_stepper(stepsPerRevolution,8,9,10,11){
	base_stepper.setSpeed(600);	
	elbow_stepper.setSpeed(600);
	shoulder_stepper.setSpeed(600);
	wrist_stepper.setSpeed(600);
}

void Arm::write_stepper(int stepper_num){
	Serial.println(this->arm_step);
	//TODO: change so that stepper is selected with stepper_num
	this->base_stepper.step(this->arm_step);
}

Arm roverarm;

void setup(){
	init();
	Serial.begin(9600);
	Serial.println("Initalized");
	
}

int main(){
	//initalize connection with ui and ros
	//run setup 
	setup();
	Serial.flush();
	//initalize buffer for serial input

	char buffer[129] = {0};
	int used = 0;//keeps track of used buffer space
	char inbyte;
	while(true){
		if(Serial.available() != 0){
		//read ASCII int from serial
		inbyte = Serial.read();
	
		//convert and add to buffer as character
		buffer[used] = char(inbyte);
		//add to buffer counter
		used++;

		if(inbyte == '\n' | inbyte == '\r'){
				
			sscanf(buffer,"%i %i\n",&roverarm.arm_num,&roverarm.arm_step);
			roverarm.write_stepper(roverarm.arm_num);

			Serial.flush();
			}
		}
	}
	return 0;
}

