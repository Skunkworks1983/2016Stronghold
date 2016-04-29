#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/AutoDriving/DriveForwardStraight.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <Commands/MultiTool/RunNewCollector.h>
#include <RobotMap.h>
#include <cstdbool>

AutoBase *AutoBase::doRockW()
{
	AutoBase *cmd = new AutoBase("Autonomous-doRockW");

	cmd->AddSequential(new DriveForwardStraight(-5, -0.6));	//Reach the defence
	cmd->AddParallel(new RotateShooter(cTOP, true));
	cmd->AddSequential(new DriveForwardStraight(-7.5, -0.6));	//breach the defence
	cmd->AddParallel(new RotateShooter(cTOP, true));

	return cmd;

}




