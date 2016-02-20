#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <RobotMap.h>

AutoBase *AutoBase::doLowB()
{
	AutoBase *cmd = new AutoBase("Autonomous-doLowB");

	cmd->AddSequential(new DriveForward(5, 1));

//	AddSequential(LowGoalCommandGroup());
}




