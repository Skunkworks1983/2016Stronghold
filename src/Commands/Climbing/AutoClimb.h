#ifndef AutoClimb_H
#define AutoClimb_H

#include <Commands/CommandGroup.h>
#define WINCH_SETPOINT 0 //not yet calibrated

class AutoClimb: public CommandGroup
{
public:
	AutoClimb(float target);
};

#endif
