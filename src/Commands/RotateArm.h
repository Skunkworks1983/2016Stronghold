#ifndef rotateArm_H
#define rotateArm_H

#include <CommandBase.h>
#include <cstdbool>

#define EPSILON .0005f
class RotateArm: public CommandBase
{
private:
	float rotateArmEncoderTicks;
	float armStartPos;
	float currentArmPos;
	float armSpeed;

public:
	RotateArm(float rotateArmEncoderTicks, float speed, float currentArmPos);
	~RotateArm();
	void Initialize();
	float getArmEncoder();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
