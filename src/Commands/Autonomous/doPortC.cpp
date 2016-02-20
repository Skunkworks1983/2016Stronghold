#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/MultiTool/CollectorMove.h>
AutoBase *AutoBase::doPortC()
{
	AutoBase *cmd = new AutoBase("Autonomous-doPortC");
	cmd->AddSequential(new CollectorMove(0.0f))
	cmd->AddSequential(new DriveForward(3, 1.0f));
	cmd->AddSequential(new CollectorMove(1.0f));
	cmd->AddSequential(new DriveForward(3, 1.0f));
	return cmd;
}




