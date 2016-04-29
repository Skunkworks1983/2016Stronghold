#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/AutoDriving/DriveForwardStraight.h>
#include <Commands/MultiTool/RotateShooter.h>

AutoBase *AutoBase::doLowB()
{
	AutoBase *cmd = new AutoBase((char*)"Autonomous-doLowB");

	cmd->AddParallel(new RotateShooter(cCollect));

	cmd->AddSequential(new DriveForwardStraight(-5, -0.35));	//Reach the defence
	cmd->AddSequential(new DriveForwardStraight(-6, -0.35));	//breach the defence

	return cmd;
}
