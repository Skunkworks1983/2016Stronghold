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
	writeToLogFile(LOGFILE_NAME, str);
	drivebase->holdAgainstTower = true;
}

void HoldAgainstTower::Execute() {
	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);
}

bool HoldAgainstTower::IsFinished() {
	char str[1024];
	sprintf(str, "stopHold %u", drivebase->stopHold);
	writeToLogFile(LOGFILE_NAME, str);
	return drivebase->stopHold;
}

void HoldAgainstTower::End() {
	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);
	char str[1024];
	sprintf(str, "HoldAgainstTower ended");
	writeToLogFile(LOGFILE_NAME, str);
}

void HoldAgainstTower::Interrupted() {
	End();
}
