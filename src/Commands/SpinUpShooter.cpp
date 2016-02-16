#include "SpinUpShooter.h"

SpinUpShooter::SpinUpShooter()
{

	oi = new OI();
	motorManager = MotorManager::getMotorManager();
	sensorManager = SensorManager::getSensorManager();



}

// Called just before this Command runs the first time
void SpinUpShooter::Initialize()
{


}

// Called repeatedly when this Command is scheduled to run
void SpinUpShooter::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool SpinUpShooter::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void SpinUpShooter::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpinUpShooter::Interrupted()
{

}
