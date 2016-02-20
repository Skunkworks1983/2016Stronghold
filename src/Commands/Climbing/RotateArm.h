#ifndef rotateArm_H
#define rotateArm_H

#include <CommandBase.h>
#include <cstdbool>


#define EPSILON .0005f
class RotateArm: public CommandBase
{
private:
	float angleDegrees; //set position it will turn

public:
	RotateArm(float angleDegrees);
	~RotateArm();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
