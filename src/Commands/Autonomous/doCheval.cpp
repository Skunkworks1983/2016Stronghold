//doCheval.cpp

#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForwardStraight.h>
#include <Commands/Driving/Turning/ArcTurn.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <Commands/MultiTool/RunNewCollector.h>
#include <RobotMap.h>
#include <cstdbool>

AutoBase *AutoBase::doCheval() {
	AutoBase*cmd = new AutoBase("Autonomous-doCheval");

#if USE_SHOOTER
	cmd->AddParallel(new RotateShooter(cTOP, true));
	cmd->AddSequential(new RunNewCollector(.3));
#endif

	cmd->AddSequential(new DriveForwardStraight(3.8, 0.25));	//Reach the defence
	cmd->AddSequential(new RotateShooter(cCollect, false, .85));
	cmd->AddSequential(new DriveForwardStraight(2.5, 0.55));
	cmd->AddParallel(new RotateShooter(cTOP));
	cmd->AddSequential(new DriveForwardStraight(2.5, 0.55));
	cmd->AddSequential(new ArcTurn(90, .80, -.5));
	cmd->AddSequential(new ArcTurn(-90, -.80, -.5));
	cmd->AddSequential(new DriveForwardStraight(1.5, 0.3));

	return cmd;
}

