#include <Commands/MultiTool/CollectorMove.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <cstdbool>


//TODO: Find the conversion ratio for encoder ticks to degrees
CollectorMove::CollectorMove(float targetDegrees)
{

	this->target = targetDegrees;
	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
}

void CollectorMove::Initialize()
{
	motorManager->enablePID(PID_ID_COLLECTOR, target);
}

void CollectorMove::Execute()
{
}

bool CollectorMove::IsFinished()
{
	return true;
	/*
	if (fabs(sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_LEFT_PORT) - target) <= COLLECTOR_ROTATOR_TOLERANCE) {
		return true;
	} else {
		return false;
	}*/
}

void CollectorMove::End()
{
	//collector->setRotatorSpeed(0.0);
	//MotorManager::getMotorManager()->disablePID(PID_ID_COLLECTOR);
}


void CollectorMove::Interrupted()
{

}
