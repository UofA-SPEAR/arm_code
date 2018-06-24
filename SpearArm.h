#ifndef Speararm_h
#define Speararm_h

//R: this file uses tabs while all others use spaces.

class Arm{

	public:
		Arm();

    //R: make a struct to define motor postiotions
    //   this makes it easier to read and safer.
    void armTo(float *targets);

	private:

    //Motor instances, one should be a DC motor
		Stepper* BaseStepper;
		Stepper* ShoulderStepper;
		Stepper* ElbowStepper;
    Stepper* WristStepper;
		Stepper* FingerStepper;

};

#endif
