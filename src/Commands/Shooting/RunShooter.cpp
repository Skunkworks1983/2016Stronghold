#include <Commands/Shooting/RunShooter.h>
#include <Services/Logger.h>
#include <Subsystems/Shooter.h>
#include <cstdio>
#include <RobotMap.h>

#define SCALING_CONSTANT .075

RunShooter::RunShooter(double speed, double timeout) :
		speed(speed), timeout(timeout) {
	Requires(shooter);
	realSpeed = 0;
	if (timeout > 0) {
		SetTimeout(timeout);
	}
}

RunShooter::~RunShooter() {
}

void RunShooter::Initialize() {
	if (fabs(speed) > .4) {
		realSpeed = speed > 0 ? .01 : -.01;
	} else {
		realSpeed = speed;
	}
	if (timeout > 0) {
		SetTimeout(timeout);
	}
	shooter->setShooterSpeed(realSpeed);
}

void RunShooter::Execute() {
	if (fabs(speed) > .4) {
		if (fabs(realSpeed * (1.0 + SCALING_CONSTANT)) < fabs(speed)) {
			realSpeed *= (1.0 + SCALING_CONSTANT);
		} else {
			realSpeed = speed;
		}
	}
	shooter->setShooterSpeed(realSpeed);
	LOG_INFO("motorPower %f speed %f leftSpeed %f rightSpeed %f", realSpeed,
			shooter->getShooterSpeed(), shooter->getLeftShooterSpeed(),
			shooter->getRightShooterSpeed());
}

bool RunShooter::IsFinished() {
	return IsTimedOut();
}

void RunShooter::Interrupted() {
	End();
}

void RunShooter::End() {
	shooter->setShooterSpeed(0);
}
