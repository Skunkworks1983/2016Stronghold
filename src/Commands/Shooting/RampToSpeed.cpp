#include <Commands/Shooting/RampToSpeed.h>
#include <Services/Logger.h>
#include <Subsystems/Shooter.h>
#include <cstdio>

#define SCALING_CONSTANT .2

RampToSpeed::RampToSpeed(double targetSpeed) :
		targetSpeed(targetSpeed) {
	realSpeed = 0.0;
}

// Called just before this Command runs the first time
void RampToSpeed::Initialize() {
	char str[1024];
	sprintf(str, "RampToSpeed Initialize called");
	Logger::getLogger()->log(str, Info);
	realSpeed = .01;
	shooter->setShooterSpeed(realSpeed);
}

// Called repeatedly when this Command is scheduled to run
void RampToSpeed::Execute() {
	if ((shooter->getLeftShooterSpeed() < targetSpeed
			|| shooter->getRightShooterSpeed() < targetSpeed)) {
		realSpeed *= (1.0 + SCALING_CONSTANT);
		shooter->setShooterSpeed(realSpeed);
	}
	char str[1024];
	sprintf(str, "RAMPING target %f leftSpeed %f rightSpeed %f", targetSpeed,
			shooter->getLeftShooterSpeed(), shooter->getRightShooterSpeed());
	Logger::getLogger()->log(str, Info);
}

// Make this return true when this Command no longer needs to run execute()
bool RampToSpeed::IsFinished() {
	return shooter->getLeftShooterSpeed() > targetSpeed
			|| shooter->getRightShooterSpeed() > targetSpeed;
}

// Called once after isFinished returns true
void RampToSpeed::End() {
	char str[1024];
	sprintf(str, "RampToSpeed End called");
	Logger::getLogger()->log(str, Info);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RampToSpeed::Interrupted() {

}
