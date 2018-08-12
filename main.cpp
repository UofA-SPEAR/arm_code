#include "SpearArm.h"
#include "StepperC.h"
#include "StepperAmis.h"
#include "Motor.h"
#include "DCMotor.h"
#include "DCPotMotor.h"

#include "common.h"

#include <math.h>
#include <string.h>

// arm needs to be a global variable since the motors need to be modified by interrupt functions
Arm* arm;

typedef enum {
    SERIAL_SUCCESS,
    SERIAL_ERROR,
} ser_err_t;

static ser_err_t handle_serial(char * buffer);
static void handle_command(char * buffer, uint32_t * armPosition);

int digitalPinToInterrupt(int pin){
    //Assumes you are on a mega
    //2 3 21 20 19 18
    switch(pin){
        case 2:
            return 0;
        case 3:
            return 1;
        case 21:
            return 2;
        case 20:
            return 3;
        case 19:
            return 4;
        case 18:
            return 5;
    }
    return -1;
}

// define interrupt functions for limit switches on stepper motors
void zeroBase() {
    arm->baseMotor.step_number = 0;
    arm->baseMotor.current_motor_radian = 0;
}
void zeroElbow() {
    arm->elbowMotor.step_number = 0;
    arm->elbowMotor.current_motor_radian = 0;
}
void zeroWristPitch() {
    arm->wristPitchMotor.step_number = 0;
    arm->wristPitchMotor.current_motor_radian = 0;
}

void setup(){
	init();
    SPI.begin();
	Serial.begin(9600);
	Serial.println("Initalized");
    delay(1000);

}

void attachInterrupts() {

    // attach interrupts for stepper motors with limit switches
    attachInterrupt(digitalPinToInterrupt(arm->baseMotor.limitSwitchPin), zeroBase, FALLING);
    attachInterrupt(digitalPinToInterrupt(arm->elbowMotor.limitSwitchPin), zeroElbow, FALLING);
    attachInterrupt(digitalPinToInterrupt(arm->wristPitchMotor.limitSwitchPin), zeroWristPitch, FALLING);
}

int main(){
    uint32_t armPosition[NUM_MOTORS];

	setup();
    arm = new Arm();
    attachInterrupts(); // this must be done AFTER arm constructor is called since arm constructor sets pin modes
    arm->wristPitchMotor.setForwardDirection(false);

    // initialize steppers that use the amis driver
    StepperAmis elbowMotorAmis(12, 2000);

    // move motors that have limit switches until they hit their limit switches
    arm->home();
    Serial.println("home");

	char buffer[8] = {0};
	buffer[SHOULDER] = (((double)400) / ((double)1023)) * UINT32_MAX; // ensure shoulder starts at a comfortable location


    for(;;){
        if (Serial.available() >= 8) {
            if (handle_serial(buffer) == SERIAL_SUCCESS) {
                handle_command(buffer, armPosition);
            } else {
                Serial.println("Packet rejected."); // Remove this
            }
        }

        arm->adjust(armPosition);
    }

	return 0;
}

/**@brief Function to read in serial and reject malformed "packets"
 */
static ser_err_t handle_serial(char * buffer) {
    Serial.readBytes(buffer, 8);

    // Error checking
    if (buffer[0] != 2 || buffer[7] != 3) { // Start or stop bytes are gone
        Serial.println("No Start/Stop Bytes!"); // remove this
        return SERIAL_ERROR;
    }

    if (buffer[6] != (uint8_t)(buffer[2] + buffer[3] + buffer[4] + buffer[5])) {
        Serial.println("Checksum Invalid!"); // remove this
        return SERIAL_ERROR;
    }

    Serial.println("Packet Accepted.");
    return SERIAL_SUCCESS;
}
static void handle_command(char * buffer, uint32_t * armPosition) {
    uint32_t angle;

    // buffer[1] is command

    memcpy(&angle, buffer + 2, sizeof(uint32_t)); // Actual data starts at buffer[2]

    //Debugging stuff, delete this
    Serial.print("Command: ");
    Serial.println(buffer[2]);
    Serial.print("Angle: ");
    Serial.println(angle);

    // Homing command (254 because thats spear_home)
    if (buffer[1] == 254) {
        arm->home();
        return;
    }

    if (buffer[1] >= NUM_MOTORS) {
        Serial.println("Incorrect command"); // delete this
        return;
    }

    // Set the correct motor to the command's angle
    armPosition[(uint8_t)buffer[1]] = angle;
}
