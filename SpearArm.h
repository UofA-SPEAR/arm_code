#ifndef Speararm_h
#define Speararm_h

class Arm{

	public:
		Arm();
    void armTo();

	private:

    //Motor instances, one should be a DC motor
		Stepper* BaseStepper;
		Stepper* ShoulderStepper;
		Stepper* ElbowStepper;
    Stepper* WristStepper;
		Stepper* FingerStepper;

    void setAllZeros();

};

#endif
