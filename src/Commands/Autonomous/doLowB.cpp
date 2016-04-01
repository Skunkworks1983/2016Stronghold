#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForwardStraight.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <Commands/MultiTool/RunNewCollector.h>

AutoBase *AutoBase::doLowB()
{
	AutoBase *cmd = new AutoBase((char*)"Autonomous-doLowB");
#if USE_SHOOTER
	cmd->AddSequential(new RunNewCollector(.3));
	cmd->AddParallel(new RotateShooter(cCollect));
#endif
	cmd->AddSequential(new DriveForwardStraight(-5, -0.35));	//Reach the defence
	cmd->AddSequential(new DriveForwardStraight(-6, -0.35));	//breach the defence

	return cmd;
}
