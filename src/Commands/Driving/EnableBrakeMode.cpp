#include <Commands/Driving/EnableBrakeMode.h>
#include <Subsystems/Drivebase.h>

EnableBrakeMode::EnableBrakeMode(bool brake, double timeout) :
		brake(brake), timeout(timeout) {
	Requires(drivebase);
}

// Called just before this Command runs the first time
void EnableBrakeMode::Initialize() {
	if (timeout > 0) {
		SetTimeout(timeout);
	}
	drivebase->setBrakeMode(brake);
	drivebase->setLeftSpeed(0.0);
	drivebase->setRightSpeed(0.0);
}

// Called repeatedly when this Command is scheduled to run
void EnableBrakeMode::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool EnableBrakeMode::IsFinished() {
	return IsTimedOut();
}

// Called once after isFinished returns true
void EnableBrakeMode::End() {
	drivebase->setBrakeMode(!brake);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void EnableBrakeMode::Interrupted() {
	End();
}
