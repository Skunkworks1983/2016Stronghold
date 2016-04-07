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
#if USE_CAN_PID
	current_left_setpoint = fmax(5.0, shooter->getLeft()->PIDGet());
	current_right_setpoint = fmax(5.0, shooter->getRight()->PIDGet());

	shooter->getRight()->SetSetpoint(current_right_setpoint);
	shooter->getLeft()->SetSetpoint(current_left_setpoint);
#else
	shooter->getRight()->SetSetpoint(leftSpeed);
	shooter->getLeft()->SetSetpoint(rightSpeed);
#endif
	shooter->getLeft()->Enable();
	shooter->getRight()->Enable();
	c = 0;
	if (timeout != 0) {
		SetTimeout(timeout);
	}
	//shooter->setRollerSpeed(Shooter::rollerDirection::KBackward, .15);
}

// Called repeatedly when this Command is scheduled to run
void PIDShot::Execute() {
	SmartDashboard::PutNumber("leftSpeed", shooter->getLeft()->PIDGet());
	SmartDashboard::PutNumber("rightSpeed", shooter->getRight()->PIDGet());
	SmartDashboard::PutNumber("time", GetFPGATime());

	const double leftDiff = fabs(shooter->getLeft()->PIDGet() - leftSpeed);
	const bool leftOnTarget = leftDiff < SHOT_TOLERANCE;
	const double rightDiff = fabs(shooter->getRight()->PIDGet() - rightSpeed);
	const bool rightOnTarget = rightDiff < SHOT_TOLERANCE;

#if USE_CAN_PID
	if (!shooter->getLeft()->isEnabled()) {
		shooter->getLeft()->Enable();
	}
	if (!shooter->getRight()->isEnabled()) {
		shooter->getRight()->Enable();
	}

	LOG_INFO(
			"PIDShot leftSpeed %f rightSpeed %f errorLeft %f errorRight %f, setpoint %f leftOut %f rightOut %f",
			shooter->getLeft()->PIDGet(), shooter->getRight()->PIDGet(),
			shooter->getLeft()->getError(), shooter->getRight()->getError(),
			shooter->getLeft()->getSetpoint(),
			shooter->getLeft()->getOutputPercentage(),
			shooter->getRight()->getOutputPercentage());

	if (current_left_setpoint < leftSpeed) {
		current_left_setpoint += 2;
	} else {
		current_left_setpoint = leftSpeed;
	}
	if (current_right_setpoint < rightSpeed) {
		current_right_setpoint += 2;
	} else {
		current_right_setpoint = rightSpeed;
	}

	shooter->getLeft()->SetSetpoint(current_left_setpoint);
	shooter->getRight()->SetSetpoint(current_right_setpoint);
#endif

	LOG_INFO(
			"PIDShot leftSpeed %f rightSpeed %f errorLeft %f errorRight %f, leftSetPoint %f, rightSetpoint %f",
			shooter->getLeft()->PIDGet(), shooter->getRight()->PIDGet(),
			shooter->getLeft()->getError(), shooter->getRight()->getError(),
			shooter->getLeft()->getSetpoint(),
			shooter->getRight()->getSetpoint());
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
//
}

// Make this return true when this Command no longer needs to run execute()
bool PIDShot::IsFinished() {
	return IsTimedOut();
}

// Called once after isFinished returns true
void PIDShot::End() {
	LOG_INFO("PIDShot End called");

	//shooter->setShooterSpeed(0.0);
	shooter->getLeft()->Disable();
	shooter->getRight()->Disable();
	shooter->getRight()->Reset();
	shooter->getLeft()->Reset();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PIDShot::Interrupted() {
	End();
}
