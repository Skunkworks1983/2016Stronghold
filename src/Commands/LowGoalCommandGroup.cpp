#include "LowGoalCommandGroup.h"

LowGoalCommandGroup::LowGoalCommandGroup()
{
/*Hopefully what this will look like:
 *
 * AddSequential(new CollectorMove(0));
 * AddSequential(new SpinUpShooter(true)); //not sure how this bit will work; how to turn it off?
 * AddParallel(new ActivateKicker()); 	   //how to make ActivateKicker() only work when the shooter is at full speed?
 *
 *
 *
 *
 */
	AddSequential(new CollectorMove(0));
//	AddSequential(new ShootGoal()); obsolete
}
