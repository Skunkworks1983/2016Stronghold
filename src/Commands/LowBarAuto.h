#ifndef LowBarAuto_H
#define LowBarAuto_H

#include <Commands/CommandGroup.h>

//#include "HighGoalCommandGroup.h"

class LowBarAuto: public CommandGroup
{
public:
	LowBarAuto(float distance, float speed, float turn);
};

#endif
