#include <Commands/Autonomous/AutoBase.h>

AutoBase *AutoBase::doPortC()
{
	AutoBase *cmd = new AutoBase("Autonomous-doPortC");
	cmd->AddSequential(new DriveForward(3, 1.0f));
	cmd->AddSequential(new CollectorMove(1.0f));
	cmd->AddSequential(new DriveForward(3, 1.0f));
	return cmd;
}




