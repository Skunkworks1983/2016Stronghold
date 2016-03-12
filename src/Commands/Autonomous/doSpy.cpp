#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/MultiTool/RotateShooter.h>

AutoBase *AutoBase::doSpy()
{
	AutoBase *cmd = new AutoBase("Autonomous-doSpy");
	cmd->AddSequential(new RotateShooter(cLowBar));
	cmd->AddSequential(new DriveForward(8, 1.0f));

	return cmd;
}



