#include <Commands/MultiTool/CollectorMove.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <cstdbool>

CollectorMove::CollectorMove(int target)
{

	this->degree = degree;
	//this->speed = speed; Speed is not passed in, would be tricky to implement with PID
	sensorManager = SensorManager::getSensorManager();

	motorManager = MotorManager::getMotorManager();

	this->target = target;
	initialCollectorPosition = collector->getRotatorPosition();

}

void CollectorMove::Initialize()
{

}

void CollectorMove::Execute()
{



}

bool CollectorMove::IsFinished()
{
return true;
}

void CollectorMove::End()
{

	collector->setRotatorSpeed(0.0);

}


void CollectorMove::Interrupted()
{

}
