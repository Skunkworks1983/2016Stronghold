#include <Commands/Shooting/RampToSpeed.h>
#include <Services/Logger.h>
#include <Subsystems/Shooter.h>
#include <cstdio>
#include <RobotMap.h>

#define SCALING_CONSTANT .5

RampToSpeed::RampToSpeed(double targetSpeed, double timeout) :
		targetSpeed(targetSpeed) {
	realSpeed = 0.0;
}

// Called just before this Command runs the first time
void RampToSpeed::Initialize() {
	LOG_INFO("RampToSpeed Initialize called");
	if (targetSpeed < 0) {
		realSpeed = -.1;
	} else if (targetSpeed > 0) {
		realSpeed = .1;
	} else {
		realSpeed = 0;
	}
	shooter->setShooterSpeed(realSpeed);
	if (timeout > 0) {
		SetTimeout(timeout);
	}
}

// Called repeatedly when this Command is scheduled to run
void RampToSpeed::Execute() {
	if (fabs(realSpeed) < fabs(targetSpeed)) {
		//realSpeed *= (1.0 + SCALING_CONSTANT);
		if (targetSpeed < 0) {
			realSpeed -= 0.05;
		} else if (targetSpeed > 0) {
			realSpeed += 0.05;
		} else {
			realSpeed = 0;
		}
	} else {
		realSpeed = targetSpeed;
	}
	shooter->setShooterSpeed(targetSpeed);

	LOG_INFO("RAMPING target %f leftSpeed %f rightSpeed %f givenSpeed %f",
			targetSpeed, shooter->getLeftShooterSpeed(),
			shooter->getRightShooterSpeed(), realSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool RampToSpeed::IsFinished() {
	return IsTimedOut();
	//return shooter->getLeftShooterSpeed() > targetSpeed || shooter->getRightShooterSpeed() > targetSpeed;
}

// Called once after isFinished returns true
void RampToSpeed::End() {
	LOG_INFO("RampToSpeed End called");
	shooter->setShooterSpeed(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RampToSpeed::Interrupted() {
	End();
}
