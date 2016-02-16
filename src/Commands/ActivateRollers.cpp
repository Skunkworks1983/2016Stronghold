#include "ActivateRollers.h"

ActivateRollers::ActivateRollers()
{
	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
	this->rollerTime = 0;
}

// Called just before this Command runs the first time
void ActivateRollers::Initialize()
{
	rollerTime = 0;
}

// Called repeatedly when this Command is scheduled to run
void ActivateRollers::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()

bool ActivateRollers::IsFinished() {

		return false;
}

// Called once after isFinished returns true
void ActivateRollers::End()
{
	collector->setRoller(Collector::KStop, 0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ActivateRollers::Interrupted()
{

}
