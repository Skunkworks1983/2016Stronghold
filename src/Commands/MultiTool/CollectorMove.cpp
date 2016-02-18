#include <Commands/MultiTool/CollectorMove.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <cstdbool>
//TODO: Find the correct target ticks for low goal, high goal, etc.
CollectorMove::CollectorMove(float target)
{

	this->target = target;
	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
	tolerance = 5;
}

void CollectorMove::Initialize()
{

}

void CollectorMove::Execute()
{
motorManager->enablePID(PID_ID_COLLECTOR, target);
}

bool CollectorMove::IsFinished()
{
	if (fabs(sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT) - target) <= tolerance) {
		return true;
	} else {
		return false;
	}
}

void CollectorMove::End()
{

	collector->setRotatorSpeed(0.0);

}


void CollectorMove::Interrupted()
{

}
