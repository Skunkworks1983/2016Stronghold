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

void ActivateRollers::Initialize()
{
	if(timeOut != 0){
		SetTimeout(timeOut);
	}
	collector->setRollerSpeed(dir, .85);
}

void ActivateRollers::Execute(){

}

bool ActivateRollers::IsFinished() {
	if(timeOut != 0 || dir == Collector::KBackward){
		return false;
	}
	return collector->getBreakBeam();
}

void ActivateRollers::End()
{
	collector->setRollerSpeed(Collector::KStop, 0);
}

void ActivateRollers::Interrupted()
{
	End();
}
