//doCheval.cpp

#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/AutoDriving/DriveForwardStraight.h>
#include <Commands/Driving/AutoDriving/DriveForwardStraightAccurate.h>
#include <Commands/Driving/Turning/PIDTurn.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <Commands/MultiTool/RunNewCollector.h>
#include <RobotMap.h>
#include <cstdbool>

AutoBase *AutoBase::doCheval() {
	AutoBase*cmd = new AutoBase("Autonomous-doCheval");

	cmd->AddSequential(new DriveForwardStraightAccurate(3.68, 0.35));	//Reach the defence
	cmd->AddSequential(new RotateShooter(cCollect, false, .85));
	cmd->AddSequential(new DriveForwardStraight(2.5, 0.75));
	cmd->AddParallel(new RotateShooter(cTOP));
	cmd->AddSequential(new DriveForwardStraight(2.5, 0.65));
	cmd->AddSequential(new PIDTurn(180.0, true, 3.5));

	return cmd;
}

