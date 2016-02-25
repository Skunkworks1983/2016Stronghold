#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <RobotMap.h>

AutoBase *AutoBase::doLowB()
{
	AutoBase *cmd = new AutoBase((char*)"Autonomous-doLowB");
	std::cout << "Reached doLowB after AutoBase cmd pointer creation" << std::endl;
	cmd->AddSequential(new DriveForward(5, 0.33));
//	does it need to handle anything after driving forward?
//	AddSequential(new TurnDegree(45)); //or until aligned with tower
//	or
//	AddSequential(Ross's function to find tower());
//	AddSequential(new DriveForward(5, 1)); // (distance to be able to score
//	AddSequential(new HighGoalCommandGroup()); not actually in this branch

	cmd->AddSequential(new DriveForward(5, 0.33));

//	AddSequential(LowGoalCommandGroup());
	return cmd;
}
