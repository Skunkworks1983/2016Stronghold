#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/MultiTool/CollectorMove.h>

AutoBase *AutoBase::doSpy()
{
	AutoBase *cmd = new AutoBase("Autonomous-doSpy");
	cmd->AddSequential(new CollectorMove(FLOOR));
	cmd->AddSequential(new DriveForward(8, 1.0f));

	return cmd;
}



