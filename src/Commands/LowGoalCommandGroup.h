#ifndef LowGoalCommandGroup_H
#define LowGoalCommandGroup_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "CollectorMove.h"
#include "SpinUpShooter.h"
#include "ActivateKicker.h"

class LowGoalCommandGroup: public CommandGroup
{
public:
	LowGoalCommandGroup();
};

#endif
