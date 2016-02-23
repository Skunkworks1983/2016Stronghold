#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/MultiTool/CollectorMove.h>
AutoBase *AutoBase::doPortC()
{
	AutoBase *cmd = new AutoBase("Autonomous-doPortC");
	//cmd->AddSequential(new CollectorMove(FLOOR));
	cmd->AddSequential(new DriveForward(3, 1.0f));
	//cmd->AddSequential(new CollectorMove(UP));
	cmd->AddSequential(new DriveForward(3, 1.0f));
	return cmd;
}




