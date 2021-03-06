#include <Commands/MultiTool/RunCollector.h>
#include <Services/Logger.h>
#include <RobotMap.h>
#include <cstdio>

#define SHOOTER_SPEED 54.0 - 2

RunCollector::RunCollector(Shooter::rollerDirection dir, float speed,
		float timeOut) :
		dir(dir), speed(speed), timeOut(timeOut) {
}

void RunCollector::Initialize() {
	LOG_INFO("RunCollector Initialize called");
	already_on = false;
	if (timeOut != 0) {
		SetTimeout(timeOut);
	}
	shooter->setRollerSpeed(dir, speed);
}

void RunCollector::Execute() {

}

bool RunCollector::IsFinished() {
	if (timeOut > 0) {
		return IsTimedOut();
	}
	if (timeOut != 0 || dir == Shooter::KBackward) {
	}
	return false;
}

void RunCollector::End() {
	LOG_INFO("RunCollector End called");
	shooter->setRollerSpeed(Shooter::KStop, 0);
}

void RunCollector::Interrupted() {
	End();
}
