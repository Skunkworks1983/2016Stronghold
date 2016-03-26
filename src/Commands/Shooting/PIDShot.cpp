#include <Commands/Shooting/PIDShot.h>
#include <Services/Logger.h>
#include <Services/ShooterMotor.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Subsystems/Shooter.h>
#include <Utility.h>
#include <cmath>
#include <RobotMap.h>
#include <cstdio>

#define SHOT_TOLERANCE .15

PIDShot::PIDShot(double leftSpeed, double rightSpeed, float timeout) :
		leftSpeed(leftSpeed), rightSpeed(rightSpeed), timeout(timeout) {
}

// Called just before this Command runs the first time
void PIDShot::Initialize() {
	LOG_INFO("PIDShot Initialize called");
	shooter->getRight()->SetSetpoint(rightSpeed - 4);
	shooter->getLeft()->SetSetpoint(leftSpeed + 3);

	shooter->getLeft()->Enable();
	shooter->getRight()->Enable();
	c = 0;
	if(timeout != 0){
		SetTimeout(timeout);
	}
}

// Called repeatedly when this Command is scheduled to run
void PIDShot::Execute() {

	SmartDashboard::PutNumber("leftSpeed", shooter->getLeftShooterSpeed());
	SmartDashboard::PutNumber("rightSpeed", shooter->getRightShooterSpeed());
	SmartDashboard::PutNumber("time", GetFPGATime());
//	LOG_INFO("PIDShot leftSpeed %f rightSpeed %f",
//			shooter->getLeftShooterSpeed(), shooter->getRightShooterSpeed());

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
	return IsTimedOut();
}

// Called once after isFinished returns true
void PIDShot::End() {
	LOG_INFO("PIDShot End called");

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
