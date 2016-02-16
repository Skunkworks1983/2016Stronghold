#ifndef BreachBasicGroup_H
#define BreachBasicGroup_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include <Commands/DriveForward.h>

class GeneralBreach: public CommandGroup
{
private:
public:
	GeneralBreach(float distance, float speed);
};

#endif
