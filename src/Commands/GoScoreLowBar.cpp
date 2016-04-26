#include <Commands/Driving/DriveForwardStraight.h>
#include <Commands/Driving/DriveForwardStraightAccurate.h>
#include <Commands/Driving/DriveTowardsTower.h>
#include <Commands/Driving/Turning/PIDTurn.h>
#include <Commands/GoScoreLowBar.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <Commands/Shooting/AutoRunCollector.h>
#include <Commands/Shooting/PIDShot.h>
#include <Commands/WaitUntilAutoTime.h>
#include <cstdbool>

GoScoreLowBar::GoScoreLowBar() {
	AddSequential(new DriveForwardStraightAccurate(-6.87, -.65, 3.0));
	AddParallel(new RotateShooter(ShooterPosition::cTOP));

	AddSequential(new PIDTurn(60, true, 3.5));
	AddSequential(new DriveForwardStraightAccurate(-1.5, -.65, 3.0));

	AddSequential(new DriveTowardsTower(-.3, .08, .75));
	AddSequential(new DriveTowardsTower(-.3, .06, .75));
	AddParallel(new DriveTowardsTower(-.3, .04));

	const double shot_speed = AUTO_SHOT_SPEED;

	AddSequential(new WaitUntilAutoTime(11));
	AddParallel(new RotateShooter(ShooterPosition::cTOP));
	AddParallel(new PIDShot(shot_speed, shot_speed, 10.0));
	AddParallel(new AutoRunCollector(true));
	AddSequential(new DriveForwardStraight(-8.5, -.3));
}
