#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForwardStraight.h>
#include <Commands/Driving/Turning/ArcTurn.h>
#include <Commands/Driving/Turning/ArcTurnToCamera.h>
#include <Commands/HighGoalPosThree.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <Commands/Shooting/AutoRunCollector.h>
#include <Commands/Shooting/PIDShot.h>
#include <cstdbool>

HighGoalPosThree::HighGoalPosThree() {
	AddSequential(new DriveForwardStraight(10, -.3));
	AddParallel(new RotateShooter(ShooterPosition::cTOP));
	AddSequential(new ArcTurn(-60, .5, .3));
	AddSequential(new DriveForwardStraight(2.0, .5));
	AddParallel(new RotateShooter(ShooterPosition::cTOP));
	AddSequential(new ArcTurn(30, -.5, .3));

	AddSequential(new DriveForwardStraight(-1.5, -.3));

	AddSequential(new ArcTurnToCamera(.75, .1, true));
	AddSequential(new DriveForwardStraight(-1.5, -.3));
	AddSequential(new ArcTurnToCamera(.75, .1, true));
	AddSequential(new DriveForwardStraight(-3.5, -.3));

	const double shot_speed = 78.0;

	AddParallel(new RotateShooter(ShooterPosition::cTOP));
	AddParallel(new PIDShot(shot_speed, shot_speed, 10.0));
	AddParallel(new AutoRunCollector(true));
	AddSequential(new DriveForwardStraight(-8.5, -.3));
}
