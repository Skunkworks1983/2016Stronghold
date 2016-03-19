#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <Commands/MultiTool/RunNewCollector.h>

AutoBase *AutoBase::doRoughT()
{
	AutoBase *cmd = new AutoBase("Autonomous-doRoughT");
	cmd->AddParallel(new RotateShooter(cTOP));
	cmd->AddSequential(new RunNewCollector(.3));
	cmd->AddSequential(new DriveForward(5, 0.55));	//Reach the defence
	cmd->AddSequential(new DriveForward(8.5, 0.55));	//breach the defence
	return cmd;
}




