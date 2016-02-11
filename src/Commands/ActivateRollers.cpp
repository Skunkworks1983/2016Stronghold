#include "ActivateRollers.h"

ActivateRollers::ActivateRollers()
{
	P = 0.0075;
	I = 0;
	D = 0;
	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
	pidController->SetPIDSourceType(PIDSourceType::kRate);
	this->rollerTime = 0;
}

// Called just before this Command runs the first time
void ActivateRollers::Initialize()
{
	pidController->SetSetpoint(1);
	pidController->Enable();
	rollerTime = 0;
}

// Called repeatedly when this Command is scheduled to run
void ActivateRollers::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool ActivateRollers::IsFinished()
{
	if (pidController->OnTarget()) {
		if (rollerTime == 0) {
			rollerTime = clock();

		}
	}
	return false;
}

// Called once after isFinished returns true
void ActivateRollers::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ActivateRollers::Interrupted()
{

}
