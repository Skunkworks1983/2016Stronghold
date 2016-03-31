#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/BangBangTurn.h>
#include <Commands/Driving/DriveForwardStraight.h>
#include <Commands/Driving/RotateTowardCameraTarget.h>
#include <Commands/GoAndScoreHighGoal.h>
#include <Commands/Shooting/AutoRunCollector.h>
#include <Commands/Shooting/PIDShot.h>
#include <cstdbool>

#define FIRST_DRIVEFORWARD 100

GoAndScoreHighGoal::GoAndScoreHighGoal() {
	AddSequential(new DriveForwardStraight(-5.25, -.3));
	AddSequential(new BangBangTurn(AutoBase::getTurnAngle(), false));
	AddSequential(new DriveForwardStraight(-2, -.3));
	//AddSequential(new BangBangTurn(0, true, 1.5));
	AddSequential(new RotateTowardCameraTarget(10));
	AddSequential(new DriveForwardStraight(-8.5, -.3));
	const double shot_speed = 77.0 - 2;

	//AddParallel(new PIDShot(shot_speed, shot_speed, 6.0));
	//AddSequential(new AutoRunCollector());

	//AddSequential(new )
}
