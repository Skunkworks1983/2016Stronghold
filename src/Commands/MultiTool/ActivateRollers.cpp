#include <Commands/MultiTool/ActivateRollers.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <Subsystems/Collector.h>

ActivateRollers::ActivateRollers(Collector::rollerDirection dir, float timeOut)
{
	Requires(collector);
	this->dir = dir;
	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
	this->timeOut = timeOut;
}

// Called just before this Command runs the first time
void ActivateRollers::Initialize()
{
	if(timeOut != 0){
		SetTimeout(timeOut);
	}
	collector->setRollerSpeed(dir, .8);
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
	End();
}
