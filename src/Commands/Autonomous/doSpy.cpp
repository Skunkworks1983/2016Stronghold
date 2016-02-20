#include <Commands/Autonomous/AutoBase.h>

AutoBase *AutoBase::doSpy()
{
	AutoBase *cmd = new AutoBase("Autonomous-doSpy");
	cmd->AddSequential(new CollectorMove(1.0f));
	cmd->AddSequential(new DriveForward(8, 1.0f));
	return cmd;
}



