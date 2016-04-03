#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForwardStraight.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <Commands/MultiTool/RunNewCollector.h>
#include <RobotMap.h>
#include <cstdbool>

AutoBase *AutoBase::doMoat() {
	AutoBase *cmd = new AutoBase("Autonomous-doMoat");
#if USE_SHOOTER
	cmd->AddParallel(new RotateShooter(cTOP, true));
	cmd->AddSequential(new RunNewCollector(.3));
#endif
	cmd->AddSequential(new DriveForwardStraight(-5, -.85f));	//Reach the defence
	cmd->AddParallel(new RotateShooter(cTOP, true));
	cmd->AddSequential(new DriveForwardStraight(-5.1, -.85f));	//breach the defence
	cmd->AddParallel(new RotateShooter(cTOP, true));
	return cmd;
}
