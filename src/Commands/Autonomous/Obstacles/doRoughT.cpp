#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/AutoDriving/DriveForwardStraight.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <Commands/MultiTool/RunNewCollector.h>
#include <RobotMap.h>
#include <cstdbool>

AutoBase *AutoBase::doRoughT()
{
	AutoBase *cmd = new AutoBase("Autonomous-doRoughT");

	cmd->AddSequential(new DriveForwardStraight(-5, -0.75));	//Reach the defence
	cmd->AddParallel(new RotateShooter(cTOP, true));

	cmd->AddSequential(new DriveForwardStraight(-8.5, -0.75));	//breach the defence
	cmd->AddParallel(new RotateShooter(cTOP, true));

	return cmd;
}




