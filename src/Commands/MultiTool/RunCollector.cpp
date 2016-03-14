#include <Commands/MultiTool/RunCollector.h>
#include <Services/Logger.h>
#include <cstdio>

#define SHOOTER_SPEED 54.0 - 2

RunCollector::RunCollector(Shooter::rollerDirection dir, float speed,
		float timeOut) :
		dir(dir), speed(speed), timeOut(timeOut) {
	Requires(shooter);
}

void RunCollector::Initialize() {
	char str[1024];
	sprintf(str, "RunCollector Initialize called");
	Logger::getLogger()->log(str, Info);
	already_on = false;
	if (timeOut != 0) {
		SetTimeout(timeOut);
	}
	shooter->setRollerSpeed(dir, 1.0);
}

void RunCollector::Execute() {
	if (shooter->getLeftShooterSpeed() > SHOOTER_SPEED
			&& shooter->getRightShooterSpeed() > SHOOTER_SPEED && !already_on) {
		already_on = true;
	}
}

bool RunCollector::IsFinished() {
	if (timeOut > 0) {
		return IsTimedOut();
	}
	if (timeOut != 0 || dir == Shooter::KBackward) {
		return false;
	}
	return shooter->getBreakBeam();
}

void RunCollector::End() {
	char str[1024];
	sprintf(str, "RunCollector End called");
	Logger::getLogger()->log(str, Info);
	shooter->setRollerSpeed(Shooter::KStop, 0);
}

void RunCollector::Interrupted() {
	End();
}
