#include <Commands/Shooting/AutoRunCollector.h>
#include <Services/Logger.h>
#include <cstdio>

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
}

void AutoRunCollector::Execute() {
	if (shooter->isUpToSpeed() && !alreadyUp) {
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
