#include <Commands/Shooting/StupidShot.h>
#include <Robot.h>
#include <RobotMap.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Subsystems/Shooter.h>
#include <Utility.h>
#include <cmath>

#define SCALING_CONSTANT .05

StupidShot::StupidShot(double targetSpeed, float timeout) :
		targetSpeed(targetSpeed), timeout(timeout) {
	Requires(shooter);
}

// Called just before this Command runs the first time
void StupidShot::Initialize() {
	if(targetSpeed < 0){
		targetPower = -1;
	}

	if (targetSpeed < 0) {
		realSpeed = -.1;
	} else if (targetSpeed > 0) {
		realSpeed = .1;
	} else {
		realSpeed = 0;
	}
	if (timeout > 0) {
		SetTimeout(timeout);
	}
	shooter->setShooterSpeed(realSpeed);
}

// Called repeatedly when this Command is scheduled to run
void StupidShot::Execute() {
	SmartDashboard::PutNumber("Left", shooter->getLeftShooterSpeed());
	SmartDashboard::PutNumber("Right", shooter->getRightShooterSpeed());
	SmartDashboard::PutNumber("Time",
			GetFPGATime() - Robot::getTeleStartTime());

	if (fabs(realSpeed) < fabs(targetSpeed)) {
		//realSpeed *= (1.0 + SCALING_CONSTANT);
		if (targetSpeed < 0) {
			realSpeed -= SCALING_CONSTANT;
		} else if (targetSpeed > 0) {
			realSpeed += SCALING_CONSTANT;
		} else {
			realSpeed = 0;
		}
	} else {
		realSpeed = targetSpeed;
	}
	shooter->setShooterSpeed(realSpeed);

	if(!alreadyUp && (fabs(shooter->getLeftShooterSpeed()) > fabs(targetSpeed) || fabs(shooter->getRightShooterSpeed()) > fabs(targetSpeed))){
		shooter->setRollerSpeed(Shooter::KForward, 1.0);
		alreadyUp = true;
	}

	LOG_INFO("RAMPING target %f givenSpeed %f leftSpeed %f rightSpeed %f",
			targetSpeed, shooter->getLeftShooterSpeed(),
			shooter->getRightShooterSpeed(), realSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool StupidShot::IsFinished() {
	return IsTimedOut();
}

// Called once after isFinished returns true
void StupidShot::End() {
	shooter->setLeftShooterSpeed(0);
	shooter->setRightShooterSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StupidShot::Interrupted() {
	End();
}
