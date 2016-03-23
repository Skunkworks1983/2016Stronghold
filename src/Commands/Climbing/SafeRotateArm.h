#ifndef SafeRotateArm_H
#define SafeRotateArm_H

#include <Commands/CommandGroup.h>

class SafeRotateArm: public CommandGroup
{
public:
	SafeRotateArm(float target);
};

#endif
