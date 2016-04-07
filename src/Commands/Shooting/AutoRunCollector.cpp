#include <Commands/Shooting/AutoRunCollector.h>
#include <Robot.h>
#include <RobotMap.h>
#include <Services/ShooterMotor.h>
#include <Utility.h>
#include <cmath>

#define SHOT_TOLERANCE .65
//in microseconds
#define AUTONOMOUS_TIMEOUT 1.0 * 1000 * 1000

#define AUTO_SHOOT 14 * 1000 * 1000

AutoRunCollector::AutoRunCollector(bool autonomous) :
		autonomous(autonomous) {
	if (timeout > 0) {
		SetTimeout(timeout);
	}
}

void AutoRunCollector::Initialize() {
	LOG_INFO("AutoRunCollector Initialize called");
	alreadyUp = false;
	c = 0;
}

void AutoRunCollector::Execute() {
	double leftDiff = fabs(
			shooter->getLeft()->PIDGet() - shooter->getLeft()->getSetpoint());
	bool leftOnTarget = (leftDiff < SHOT_TOLERANCE);
	double rightDiff = fabs(
			shooter->getRight()->PIDGet() - shooter->getRight()->getSetpoint());
	bool rightOnTarget = (rightDiff < SHOT_TOLERANCE);

	double rightLeftDiff = fabs(shooter->getRight()->PIDGet())
			- fabs(shooter->getLeft()->PIDGet());

	if (leftOnTarget && rightOnTarget && shooter->getLeft()->getSetpoint() != 0
			&& shooter->getRight()->getSetpoint() != 0) {
		c++;
		if (c >= 3) {
			c = 3;
		}
	} else {
		c = 0;
	}

	LOG_INFO(
	 "leftSpeed %f rightSpeed %f leftDiff %f rightDiff %f leftOnTarget differenceright-left %f",
	 shooter->getLeft()->PIDGet(), shooter->getRight()->PIDGet(),
	 leftDiff, rightDiff, rightLeftDiff);

	if ((c >= 3 || (autonomous && GetFPGATime() - Robot::getAutoStartTime() > AUTO_SHOOT))  && !alreadyUp) {
		shooter->setRollerSpeed(Shooter::KForward, 1.0);
		alreadyUp = true;
		LOG_INFO("Shot Speed L: %f R: %f", shooter->getLeft()->PIDGet(),
				shooter->getRight()->PIDGet());
		if (autonomous) {
			startingTime = GetFPGATime();
		}
	}

	if (autonomous && startingTime > 0 && GetFPGATime() > startingTime + AUTONOMOUS_TIMEOUT) {
		shooter->getLeft()->Disable();
		shooter->getRight()->Disable();
		shooter->getRight()->Reset();
		shooter->getLeft()->Reset();
		End();
	}
}

bool AutoRunCollector::IsFinished() {
	return false;
}

void AutoRunCollector::End() {
	shooter->setRollerSpeed(Shooter::KStop, 0);
	LOG_INFO("THIS IS WHERE THE AUTORUNCOLLECTOR ENDS ENDS ENDS");
}

void AutoRunCollector::Interrupted() {
	End();
}
