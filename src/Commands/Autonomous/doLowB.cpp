#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/MultiTool/RotateShooter.h>

AutoBase *AutoBase::doLowB()
{
	AutoBase *cmd = new AutoBase((char*)"Autonomous-doLowB");
	cmd->AddSequential(new RotateShooter(cLowBar));
	cmd->AddSequential(new DriveForward(5, 0.35));	//Reach the defence
	cmd->AddSequential(new DriveForward(6, 0.35));	//breach the defence

	return cmd;
}
