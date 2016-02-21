#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>

AutoBase *AutoBase::doRoughT()
{
	AutoBase *cmd = new AutoBase("Autonomous-doRoughT");

	cmd->AddSequential(new DriveForward(2000, .3));

	return cmd;
}




