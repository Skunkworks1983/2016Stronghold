#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForwardStraight.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <Commands/MultiTool/RunNewCollector.h>
#include <RobotMap.h>
#include <cstdbool>

AutoBase *AutoBase::doRamP() {
	AutoBase *cmd = new AutoBase("Autonomous-doRamP");
#if USE_SHOOTER
	cmd->AddParallel(new RotateShooter(cTOP, true));
	cmd->AddSequential(new RunNewCollector(.3));
#endif
	cmd->AddSequential(new DriveForwardStraight(-5, -0.75));	//Reach the defence
	cmd->AddSequential(new DriveForwardStraight(-6.5, -0.75));	//breach the defence
	return cmd;
}

