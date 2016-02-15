#include "LowBarAuto.h"

LowBarAuto::LowBarAuto()
{
	AddSequential(new DriveForward(5, 1));
	AddSequential(new TurnDegree(45)); //or until aligned with tower
//	or
//	AddSequential(Ross's function to find tower());
	AddSequential(new DriveForward(5, 1)); // (distance to be able to score
//	AddSequential(new HighGoalCommandGroup()); not actually in this branch
//	or
//	AddSequential(LowGoalCommandGroup());


}
