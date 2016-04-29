#include <Commands/Autonomous/GoAndScoreHighGoal2.h>
#include <Commands/Driving/AutoDriving/DriveForwardStraight.h>
#include <Commands/Driving/AutoDriving/GoToBatter.h>
#include <Commands/MultiTool/RotateShooter.h>
#include <Commands/Shooting/AutoRunCollector.h>
#include <Commands/Shooting/PIDShot.h>
#include <Commands/WaitUntilAutoTime.h>
#include <cstdbool>

GoAndScoreHighGoal2::GoAndScoreHighGoal2() {
	AddParallel(new RotateShooter(ShooterPosition::cTOP));

	AddParallel(new GoToBatter());
	AddSequential(new WaitUntilAutoTime(11.0));

	const double shot_speed = 70.0;

	AddParallel(new RotateShooter(ShooterPosition::cTOP));
	AddParallel(new PIDShot(shot_speed, shot_speed, 10.0));
	AddParallel(new AutoRunCollector(true));
	AddSequential(new DriveForwardStraight(-8.5, -.3));
}
