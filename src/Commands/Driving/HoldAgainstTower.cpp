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
	drivebase->setHold(true);
	LOG_INFO("HoldAgainstTower Started");
}

void HoldAgainstTower::Execute() {
	drivebase->setLeftSpeed(speed, speed, 0);
	drivebase->setRightSpeed(speed, speed, 0);
}

bool HoldAgainstTower::IsFinished() {
	return false;
}

void HoldAgainstTower::End() {
	/*drivebase->setLeftSpeed(0);
	 drivebase->setRightSpeed(0);*/
	drivebase->setLeftSpeed(0);
	 drivebase->setRightSpeed(0);
	drivebase->setHold(true);
	LOG_INFO("HoldAgainstTower ended");
}

void HoldAgainstTower::Interrupted() {
	End();
}
