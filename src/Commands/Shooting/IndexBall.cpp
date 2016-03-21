#include <Commands/MultiTool/RunCollector.h>
#include <Commands/Shooting/IndexBall.h>
#include <Commands/Shooting/BangBangControl.h>
#include <Commands/Shooting/PIDShot.h>
#include <Commands/Shooting/RampToSpeed.h>
#include <Subsystems/Shooter.h>

IndexBall::IndexBall() {
	const double shooter_batter_speed = 54.65;
	AddSequential(new RunCollector(Shooter::KBackward, 1.0, .1));
	AddSequential(new RunCollector(Shooter::KForward, 1.0, .15));
	AddSequential(new RunCollector(Shooter::KBackward, 1.0, .3));
}
