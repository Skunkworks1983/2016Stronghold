#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForwardStraight.h>
#include <Commands/Driving/Turning/ArcTurn.h>
#include <Commands/Driving/Turning/ArcTurnToCamera.h>
#include <Commands/GoAndScoreHighGoal.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <Commands/Shooting/AutoRunCollector.h>
#include <Commands/Shooting/PIDShot.h>
#include <cstdbool>

#define FIRST_DRIVEFORWARD 100

GoAndScoreHighGoal::GoAndScoreHighGoal() {

	AddSequential(new DriveForwardStraight(AutoBase::getFirstDistance(), -.3));
	AddParallel(new RotateShooter(ShooterPosition::cTOP));

	AddSequential(new ArcTurn(AutoBase::getTurnData()));
	AddSequential(new DriveForwardStraight(AutoBase::getMiddleDistance(), -.5));
	AddParallel(new RotateShooter(ShooterPosition::cTOP));
	AddSequential(new ArcTurn(AutoBase::getSecondTurnData()));

	AddSequential(new DriveForwardStraight(-1, -.3));

	AddSequential(new ArcTurnToCamera(.75, .1, true, 1.5));
	AddSequential(new DriveForwardStraight(-.75, -.3));
	AddSequential(new ArcTurnToCamera(.75, .1, true, 1.5));
	AddSequential(new DriveForwardStraight(-.75, -.3));
	AddSequential(new ArcTurnToCamera(.75, .1, true, 1.5));

	const double shot_speed = 70.0;

	AddSequential(new DriveForwardStraight(-8.5, -.45, 1.0));
	AddParallel(new RotateShooter(ShooterPosition::cTOP));
	AddParallel(new PIDShot(shot_speed, shot_speed, 10.0));
	AddParallel(new AutoRunCollector(true));
	AddSequential(new DriveForwardStraight(-8.5, -.3));

}
