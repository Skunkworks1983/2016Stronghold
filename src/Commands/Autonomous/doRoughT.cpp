#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/MultiTool/RotateShooter.h>

AutoBase *AutoBase::doRoughT()
{
	AutoBase *cmd = new AutoBase("Autonomous-doRoughT");
	cmd->AddSequential(new RotateShooter(cTOP));
	cmd->AddSequential(new DriveForward(5, 0.55));	//Reach the defence
	cmd->AddSequential(new DriveForward(8.5, 0.55));	//breach the defence
	return cmd;
}




