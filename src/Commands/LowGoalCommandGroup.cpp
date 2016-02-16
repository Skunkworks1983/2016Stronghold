#include "LowGoalCommandGroup.h"

LowGoalCommandGroup::LowGoalCommandGroup()
{
	AddSequential(new CollectorMove(0));
	AddSequential(new SpinUpShooter());
	AddSequential(new ActivateKicker());
}
