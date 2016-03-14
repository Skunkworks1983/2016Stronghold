#include <Commands/Driving/HoldAgainstTower.h>
#include <Services/Logger.h>
#include <Subsystems/Drivebase.h>
#include <cstdio>
#include <RobotMap.h>

HoldAgainstTower::HoldAgainstTower(float speed) :
		speed(speed) {
	Requires(drivebase);

}

void HoldAgainstTower::Initialize() {
	char str[1024];
	sprintf(str, "HoldAgainstTower Started");
	Logger::getLogger()->log(str, Info);
	drivebase->setHold(true);
}

void HoldAgainstTower::Execute() {
	drivebase->setLeftSpeed(speed, speed, 0);
	drivebase->setRightSpeed(speed, speed, 0);
}

bool HoldAgainstTower::IsFinished() {
	return false;
}

void HoldAgainstTower::End() {
	drivebase->setLeftSpeed(0);
	 drivebase->setRightSpeed(0);
	drivebase->setHold(true);

	char str[1024];
	sprintf(str, "HoldAgainstTower ended");
	Logger::getLogger()->log(str, Info);
}

void HoldAgainstTower::Interrupted() {
	End();
}
