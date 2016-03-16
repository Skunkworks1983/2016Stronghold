#include <Commands/Shooting/PIDShot.h>
#include <Services/Logger.h>
#include <Services/ShooterMotor.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Subsystems/Shooter.h>
#include <Utility.h>
#include <cmath>
#include <cstdio>

#define SHOT_TOLERANCE .15

PIDShot::PIDShot(double leftSpeed, double rightSpeed) :
		leftSpeed(leftSpeed), rightSpeed(rightSpeed) {
}

// Called just before this Command runs the first time
void PIDShot::Initialize() {
	char str[1024];
	sprintf(str, "PIDShot Initialize called");
	Logger::getLogger()->log(str, Info);
	shooter->getRight()->SetSetpoint(rightSpeed);
	shooter->getLeft()->SetSetpoint(leftSpeed);

	shooter->getLeft()->Enable();
	shooter->getRight()->Enable();
	c = 0;
}

// Called repeatedly when this Command is scheduled to run
void PIDShot::Execute() {

	SmartDashboard::PutNumber("leftSpeed", shooter->getLeftShooterSpeed());
	SmartDashboard::PutNumber("rightSpeed", shooter->getRightShooterSpeed());
	SmartDashboard::PutNumber("time", GetFPGATime());
//	const double leftDiff = fabs(shooter->getLeft()->PIDGet() - leftSpeed);
//	const bool leftOnTarget = leftDiff < SHOT_TOLERANCE;
//	const double rightDiff = fabs(shooter->getRight()->PIDGet() - rightSpeed);
//	const bool rightOnTarget = rightDiff < SHOT_TOLERANCE;
//
//	char str[1024];
//	sprintf(str, "PIDShot leftSpeed %f rightSpeed %f, diffleft %f, diffRight %f",
//			shooter->getLeftShooterSpeed(), shooter->getRightShooterSpeed(), leftDiff, rightDiff);
//	Logger::getLogger()->log(str, Info);
//
//	if (leftOnTarget && rightOnTarget) {
//		c++;
//	} else {
//		c--;
//		if(c < 0){
//			c = 0;
//		}
//	}
//
//	if (c > 5) {
//		shooter->setUpToSpeed(true);
//	} else {
//		shooter->setUpToSpeed(false);
//	}
}

// Make this return true when this Command no longer needs to run execute()
bool PIDShot::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void PIDShot::End() {
	char str[1024];
	sprintf(str, "PIDShot End called");
	Logger::getLogger()->log(str, Info);

	shooter->setShooterSpeed(0.0);
	shooter->getLeft()->Disable();
	shooter->getRight()->Disable();
	shooter->getLeft()->Reset();
	shooter->getRight()->Reset();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PIDShot::Interrupted() {
	End();
}
