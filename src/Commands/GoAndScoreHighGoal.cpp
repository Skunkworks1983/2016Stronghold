#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForwardStraight.h>
#include <Commands/Driving/Turning/ArcTurn.h>
#include <Commands/Driving/Turning/ArcTurnToCamera.h>
#include <Commands/GoAndScoreHighGoal.h>

#define FIRST_DRIVEFORWARD 100

GoAndScoreHighGoal::GoAndScoreHighGoal() {
	AddSequential(new DriveForwardStraight(AutoBase::getFirstDistance(), -.3));
	//AddSequential(new BangBangTurn(AutoBase::getTurnAngle(), false));
	AddSequential(new ArcTurn(AutoBase::getTurnAngle(), -0.75, -.3));
	AddSequential(new DriveForwardStraight(-2.0, -.5));
	AddSequential(new ArcTurn(AutoBase::getSecondTurnAngle(), -0.75, -.3));

	AddSequential(new DriveForwardStraight(-1, -.3));
	//AddSequential(new BangBangTurn(0, true, 1.5));
	AddSequential(new ArcTurnToCamera(.75,.1));
	//AddSequential(new RotateTowardCameraTarget(10));
	AddSequential(new DriveForwardStraight(-8.5, -.3));
	const double shot_speed = 77.0 - 2;

	//AddParallel(new PIDShot(shot_speed, shot_speed, 6.0));
	//AddSequential(new AutoRunCollector());

	//AddSequential(new )
}
