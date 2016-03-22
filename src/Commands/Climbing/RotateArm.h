#ifndef rotateArm_H
#define rotateArm_H

#include <CommandBase.h>
#include <cstdbool>
#define EPSILON 250

class RotateArm: public CommandBase
{
private:
	float target; //set position it will turn
public:
	RotateArm(float target);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
