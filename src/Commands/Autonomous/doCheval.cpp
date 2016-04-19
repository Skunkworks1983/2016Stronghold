//doCheval.cpp

#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
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
	cmd->AddSequential(new RunNewCollector(.4));
#endif

	cmd->AddSequential(new DriveForwardStraight(3.65, 0.25));	//Reach the defence
	cmd->AddSequential(new RotateShooter(cCollect, false, .85));
	cmd->AddSequential(new DriveForwardStraight(2.5, 0.55));
	cmd->AddParallel(new RotateShooter(cTOP));
	cmd->AddSequential(new DriveForwardStraight(2.5, 0.55));
	cmd->AddSequential(new ArcTurn(90, .80, -.75, true));
	cmd->AddSequential(new DriveForward(-.70, -0.5));
	cmd->AddSequential(new ArcTurn(0, -.80, -.75, true));

	return cmd;
}

