#include <Commands/Autonomous/AutoBase.h>

AutoBase *AutoBase::doRoughT()
{
	AutoBase *cmd = new AutoBase("Autonomous-doRoughT");
	cmd->AddSequential(new CollectorMove(1.0f));
	cmd->AddSequential(new DriveForward(8, 1.0));
	return cmd;
}




