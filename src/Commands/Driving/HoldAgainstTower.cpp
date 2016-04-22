#include <Commands/Driving/HoldAgainstTower.h>
#include <RobotMap.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Subsystems/Drivebase.h>

HoldAgainstTower::HoldAgainstTower(float speed) :
		speed(speed) {
	Requires(drivebase);

}

void HoldAgainstTower::Initialize() {
	SmartDashboard::PutNumber("speed",speed);
	LOG_INFO("HoldAgainstTower Started");
}

void HoldAgainstTower::Execute() {
	speed = SmartDashboard::GetNumber("speed", speed);
	LOG_INFO("DynamicSpeed at %f", speed);
	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);
}

bool HoldAgainstTower::IsFinished() {
	return false;
}

void HoldAgainstTower::End() {
	drivebase->setLeftSpeed(0);
	 drivebase->setRightSpeed(0);
	drivebase->setHold(true);
	LOG_INFO("HoldAgainstTower ended");
}

void HoldAgainstTower::Interrupted() {
	End();
}
