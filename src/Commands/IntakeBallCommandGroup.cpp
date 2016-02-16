#include "IntakeBallCommandGroup.h"

IntakeBallCommandGroup::IntakeBallCommandGroup()
{
	AddSequential(new CollectorMove(0));
	AddSequential(new ActivateRollers());
}
