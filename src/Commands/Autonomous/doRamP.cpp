#include <Commands/Autonomous/AutoBase.h>

AutoBase *AutoBase::doRamP()
{
	AutoBase *cmd = new AutoBase("Autonomous-doRamP");
	cmd->AddSequential(new DriveForward(7, 1.0))
	return cmd;
}




