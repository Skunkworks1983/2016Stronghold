#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForwardStraight.h>
#include <Commands/Driving/Turning/ArcTurn.h>
#include <RobotMap.h>
#include <cstdbool>

AutoBase *AutoBase::doRockW()
{
	AutoBase *cmd = new AutoBase("Autonomous-doRockW");
#if USE_SHOOTER
	cmd->AddParallel(new RotateShooter(cTOP, true));
	cmd->AddSequential(new RunNewCollector(.3));
#endif
	cmd->AddSequential(new DriveForwardStraight(-5, -0.75));	//Reach the defence

	cmd->AddSequential(new ArcTurn(0.0, 0.75, 0.1, true));

	cmd->AddSequential(new DriveForwardStraight(-6.5, -0.75));	//breach the defence
	return cmd;

}




