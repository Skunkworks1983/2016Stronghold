#include <Commands/Shooting/AutoRunCollector.h>
#include <Services/Logger.h>
#include <Services/ShooterMotor.h>
#include <cmath>
#include <cstdio>

#define SHOT_TOLERANCE .3

AutoRunCollector::AutoRunCollector() {
	if (timeout > 0) {
		SetTimeout(timeout);
	}
}

void AutoRunCollector::Initialize() {
	char str[1024];
	sprintf(str, "AutoRunCollector Initialize called");
	Logger::getLogger()->log(str, Info);
	alreadyUp = false;
	c = 0;
}

void AutoRunCollector::Execute() {
	double leftDiff = fabs(
			shooter->getLeft()->PIDGet() - shooter->getLeft()->getSetpoint());
	bool leftOnTarget = leftDiff < SHOT_TOLERANCE;
	double rightDiff = fabs(
			shooter->getRight()->PIDGet() - shooter->getRight()->getSetpoint());
	bool rightOnTarget = rightDiff < SHOT_TOLERANCE;

	if (leftOnTarget && rightOnTarget && shooter->getLeft()->getSetpoint() != 0
			&& shooter->getRight()->getSetpoint() != 0) {
		c++;
		if (c > 10) {
			c = 10;
		}
	} else {
		c = 0;
		/*c--;
		 if(c < 0){
		 c= 0;
		 }*/
	}

	char str[1024];
	sprintf(str, "leftDiff %f rightDiff %f leftOnTarget %u rightOnTarget %u c: %u",
			leftDiff, rightDiff, leftOnTarget, rightOnTarget, c);
	Logger::getLogger()->log(str, Info);

	if (c > 5 && !alreadyUp) {
		shooter->setRollerSpeed(Shooter::KForward, 1.0);
		alreadyUp = true;
		char str[1024];
		sprintf(str, "THIS IS WHERE THE AUTORUNCOLLECTOR STARTS STARTS STARTS");
		Logger::getLogger()->log(str, Info);
	}
}

bool AutoRunCollector::IsFinished() {
	return false;
}

void AutoRunCollector::End() {
	shooter->setRollerSpeed(Shooter::KStop, 0);
	char str[1024];
	sprintf(str, "THIS IS WHERE THE AUTORUNCOLLECTOR ENDS ENDS ENDS");
	Logger::getLogger()->log(str, Info);
}

void AutoRunCollector::Interrupted() {
	End();
}
