#include <Commands/Shooting/AutoRunCollector.h>
#include <Services/Logger.h>
#include <Services/ShooterMotor.h>
#include <cmath>
#include <cstdio>
#include <RobotMap.h>

#define SHOT_TOLERANCE .65

AutoRunCollector::AutoRunCollector() {
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
	double rightDiff = fabs(shooter->getRight()->PIDGet() - shooter->getRight()->getSetpoint());
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
		/*c--;
		 if(c < 0){
		 c= 0;
		 }*/
	}

	LOG_INFO(
			"leftSpeed %f rightSpeed %f leftDiff %f rightDiff %f leftOnTarget differenceright-left %f",
			shooter->getLeft()->PIDGet(), shooter->getRight()->PIDGet(),
			leftDiff, rightDiff, rightLeftDiff);

	if (c >= 3 && !alreadyUp) {
		shooter->setRollerSpeed(Shooter::KForward, 1.0);
		alreadyUp = true;
		LOG_INFO("THIS IS WHERE THE AUTORUNCOLLECTOR STARTS STARTS STARTS");
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
