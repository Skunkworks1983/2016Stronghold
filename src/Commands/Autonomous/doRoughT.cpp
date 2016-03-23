#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForwardStraight.h>
#include <RobotMap.h>

AutoBase *AutoBase::doRoughT()
{
	AutoBase *cmd = new AutoBase("Autonomous-doRoughT");
#if USE_SHOOTER
	cmd->AddParallel(new RotateShooter(cTOP));
	cmd->AddSequential(new RunNewCollector(.3));
#endif
	cmd->AddSequential(new DriveForwardStraight(5, 0.75));	//Reach the defence
	cmd->AddSequential(new DriveForwardStraight(8.5, 0.75));	//breach the defence
	return cmd;
}




