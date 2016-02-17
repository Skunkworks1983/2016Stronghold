#include "CollectorUp.h"

CollectorUp::CollectorUp(float currentTurnPos, double turnPos, float speed)
{
	Requires(collector);
	this->currentTurnPos = currentTurnPos;
	this->turnPos = turnPos;
	//this->startPos = 0;
	this->speed = speed;
}

// Called just before this Command runs the first time
void CollectorUp::Initialize()
{
	collector->resetEncoder();
	MotorManager::getMotorManager()->setPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT,turnPos);
	//MotorManager::getMotorManager()->setSpeed(COLLECTOR_MOTOR_PORT, speed);
}

// Called repeatedly when this Command is scheduled to run
void CollectorUp::Execute()
{
	//SensorManager::getSensorManager()->GetSpeed(COLLECTOR_MOTOR_PORT);
	currentTurnPos = SensorManager::getSensorManager()->GetEncoderPosition(COLLECTOR_ROTATOR_MOTOR_1_PORT);
	if (turnPos-currentTurnPos < EPSILON){
		MotorManager::getMotorManager()->setSpeed(COLLECTOR_ROTATOR_MOTOR_1_PORT, 0);
		//disable enable pid instead.

	}
}

// Make this return true when this Command no longer needs to run execute()
bool CollectorUp::IsFinished()
{
	if (turnPos-currentTurnPos < EPSILON){
			return true;
	}
	else {
			return false;  }

}

// Called once after isFinished returns true
void CollectorUp::End()
{
	MotorManager::getMotorManager()->setSpeed(COLLECTOR_MOTOR_PORT, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CollectorUp::Interrupted()
{
	End();
}
