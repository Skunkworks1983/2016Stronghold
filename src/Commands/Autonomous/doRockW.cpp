#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>

AutoBase *AutoBase::doRockW()
{
	AutoBase *cmd = new AutoBase("Autonomous-doRockW");
	cmd->AddSequential(new DriveForward(8, 1.0));

	return cmd;

}




