#include <Commands/MultiTool/ActivateRollers.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <Subsystems/Collector.h>

ActivateRollers::ActivateRollers(float timeOut)
{
	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
	this->timeOut = timeOut;
}

// Called just before this Command runs the first time
void ActivateRollers::Initialize()
{
	SetTimeout(timeOut);
	collector->setRollerSpeed(Collector::KForward, 1);

}

// Called repeatedly when this Command is scheduled to run
void ActivateRollers::Execute(){

}

// Make this return true when this Command no longer needs to run execute()

bool ActivateRollers::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ActivateRollers::End()
{
	collector->setRollerSpeed(Collector::KStop, 0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ActivateRollers::Interrupted()
{

}
