#include <Commands/Shooting/SpinUpShooter.h>
#include <OI.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>

SpinUpShooter::SpinUpShooter(float timeOut, float speed)
{

	oi = new OI();
	motorManager = MotorManager::getMotorManager();
	sensorManager = SensorManager::getSensorManager();

	this->timeOut = timeOut;



}

// Called just before this Command runs the first time
void SpinUpShooter::Initialize()
{


SetTimeout(timeOut);
}

// Called repeatedly when this Command is scheduled to run
void SpinUpShooter::Execute()
{
motorManager->enablePID(PID_ID_SHOOTER_1, speed);
motorManager->enablePID(PID_ID_SHOOTER_1, speed);

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
