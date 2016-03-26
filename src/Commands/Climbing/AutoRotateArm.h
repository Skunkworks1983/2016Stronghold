#ifndef AutoRotateArm_H
#define AutoRotateArm_H

#include <CommandBase.h>
#include <cstdbool>

#define EPSILON_UP 250
#define ARM_WIGGLE_TOLERANCE_PERCENT 0.05f
#define CONTINUE_CLILMB_COUNTER 25

class AutoRotateArm: public CommandBase
{
private:
	float target;
	bool continueClimbing; //IsFinished check
public:
	AutoRotateArm(float target);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	double lastEnc;		//Used for delta encoder
	double curEnc;
	int curIt;
};

#endif
