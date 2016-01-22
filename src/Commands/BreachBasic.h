#ifndef BreachBasicGroup_H
#define BreachBasicGroup_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include <Commands/DriveForward.h>

class BreachBasicGroup: public CommandGroup
{
private:
	double distance;
	double speed;
public:
	BreachBasicGroup();
};

#endif
