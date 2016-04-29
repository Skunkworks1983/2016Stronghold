#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Autonomous/GoAndScoreHighGoal.h>
#include <Commands/Driving/AutoDriving/DriveForwardStraight.h>
#include <Commands/Driving/AutoDriving/DriveForwardStraightAccurate.h>
#include <Commands/Driving/AutoDriving/DriveTowardsTower.h>
#include <Commands/Driving/Turning/PIDTurn.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <Commands/Shooting/AutoRunCollector.h>
#include <Commands/Shooting/PIDShot.h>
#include <Commands/WaitUntilAutoTime.h>
#include <TuningValues.h>
#include <cstdbool>

#define FIRST_DRIVEFORWARD 100

#define NO_ANGLE_CHECK(x) (x == 420 ? 0 : x)
#define NO_ANGLE_RELATIVE(x) (x == 420 ? false : true)

GoAndScoreHighGoal::GoAndScoreHighGoal() {

	AddSequential(new DriveForwardStraightAccurate(AutoBase::getFirstDistance(), -.65, 3.0));
	AddParallel(new RotateShooter(ShooterPosition::cTOP));

	AddSequential(new PIDTurn(NO_ANGLE_CHECK(AutoBase::getFirstTurnAngle()), NO_ANGLE_RELATIVE(AutoBase::getFirstTurnAngle()), 3.5));
	AddSequential(new DriveForwardStraightAccurate(AutoBase::getMiddleDistance(), -.65, 3.0));
	AddSequential(new PIDTurn(NO_ANGLE_CHECK(AutoBase::getSecondTurnAngle()), NO_ANGLE_RELATIVE(AutoBase::getSecondTurnAngle()), 3.5));

	AddSequential(new DriveTowardsTower(-.3, .08, .75));
	AddSequential(new DriveTowardsTower(-.3, .06, .75));
	AddParallel(new DriveTowardsTower(-.3, .04));

	const double shot_speed = AUTO_SHOT_SPEED;

	AddSequential(new WaitUntilAutoTime(12.5));
	AddParallel(new RotateShooter(ShooterPosition::cTOP));
	AddParallel(new PIDShot(shot_speed, shot_speed, 10.0));
	AddParallel(new AutoRunCollector(true));
	AddSequential(new DriveForwardStraight(-8.5, -.3));

}
