#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForwardStraight.h>
#include <Commands/Driving/Turning/BangBangTurn.h>
#include <Commands/Driving/Turning/RotateTowardCameraTarget.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <Commands/MultiTool/RunNewCollector.h>
#include <Commands/Shooting/AutoRunCollector.h>
#include <Commands/Shooting/PIDShot.h>
#include <Commands/TimeOut.h>
#include <cstdbool>

AutoBase *AutoBase::doLowBarandScore() {
	AutoBase *cmd = new AutoBase((char*) "Autonomous-doLowB");
	cmd->AddSequential(AutoBase::doLowB());

	cmd->AddSequential(new RunNewCollector(.3));
	cmd->AddParallel(new RotateShooter(cCollect));
	cmd->AddSequential(new DriveForwardStraight(-5, -0.4));	//Reach the defence
	cmd->AddSequential(new DriveForwardStraight(-11.02, -0.4));	//breach the defence
	cmd->AddParallel(new RotateShooter(cTOP));
	cmd->AddSequential(new BangBangTurn(60, false, 1.2));

	cmd->AddSequential(new DriveForwardStraight(-3, -0.2));

	const double shot_speed = 77.0 - 4.5;
	cmd->AddParallel(new PIDShot(shot_speed + 1, shot_speed - 1));
	cmd->AddParallel(new RotateTowardCameraTarget(5));
	cmd->AddSequential(new AutoRunCollector());
	cmd->AddSequential(new TimeOut(15));
	return cmd;
}
