#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/DriveForward.h>
#include <Commands/Driving/DriveForwardStraight.h>
#include <Commands/Driving/DriveTowardsTower.h>
#include <Commands/Driving/Turning/PIDTurn.h>
#include <Commands/GoAndScoreHighGoal.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <Commands/Shooting/AutoRunCollector.h>
#include <Commands/Shooting/PIDShot.h>
#include <Commands/WaitUntilAutoTime.h>
#include <cstdbool>

#define FIRST_DRIVEFORWARD 100

GoAndScoreHighGoal::GoAndScoreHighGoal() {

	AddSequential(new DriveForwardStraight(AutoBase::getFirstDistance(), -.3));
	AddParallel(new RotateShooter(ShooterPosition::cTOP));

	AddSequential(new PIDTurn(AutoBase::getTurnData()));
//	AddSequential(new RunNewCollector(.25));
	AddSequential(new DriveForward(AutoBase::getMiddleDistance(), -.3));
//	AddSequential(new RunNewCollector(.25));
	AddSequential(new PIDTurn(AutoBase::getSecondTurnData()));
//	AddSequential(new RunNewCollector(.25));

	AddSequential(new DriveTowardsTower(-.3, .08, 1.0));
	AddSequential(new DriveTowardsTower(-.3, .06, 1.0));
	AddParallel(new DriveTowardsTower(-.3, .04));

	const double shot_speed = 75.0;

	AddSequential(new WaitUntilAutoTime(12));
	AddParallel(new RotateShooter(ShooterPosition::cTOP));
	AddParallel(new PIDShot(shot_speed, shot_speed, 10.0));
	AddParallel(new AutoRunCollector(true));
	AddSequential(new DriveForwardStraight(-8.5, -.3));

}
