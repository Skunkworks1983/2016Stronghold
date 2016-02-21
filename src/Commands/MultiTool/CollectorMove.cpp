#include <Commands/MultiTool/CollectorMove.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
#include <cstdbool>


//TODO: Find the conversion ratio for encoder ticks to degrees
CollectorMove::CollectorMove(float targetDegrees)
{

	this->target = targetDegrees * COLLECTOR_ENCODER_TICKS_PER_DEGREE;
	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
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
	if (fabs(sensorManager->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_LEFT_PORT) - target) <= COLLECTOR_ROTATOR_TOLERANCE) {
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
