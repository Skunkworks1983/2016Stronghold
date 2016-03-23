#include <Commands/Driving/TankDrive.h>
#include <DriverStation.h>
#include <OI.h>
#include <Subsystems/Drivebase.h>

TankDrive::TankDrive() {
	Requires(drivebase);
}

// Called just before this Command runs the first time
void TankDrive::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void TankDrive::Execute() {
	if (oi->getLeftStickY() > .5) {
		drivebase->setHold(false);
	}
	if (fabs(oi->getLeftStickY()) > .8 || fabs(oi->getRightStickY()) > .8) {
		drivebase->setDriverControl(true);
	}
	if (drivebase->isDriverControl() && DriverStation::GetInstance().IsOperatorControl() && !DriverStation::GetInstance().IsAutonomous()) {
		drivebase->setLeftSpeed(oi->getLeftStickY());
		drivebase->setRightSpeed(oi->getRightStickY());
	}

}

// Make this return true when this Command no longer needs to run execute()
bool TankDrive::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TankDrive::End() {
	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TankDrive::Interrupted() {
	End();
}
