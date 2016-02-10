#include "SpinUpShooter.h"

SpinUpShooter::SpinUpShooter()
{

	oi = new OI();
	motormanager = MotorManager::getMotorManager();
	sensormanager = SensorManager::getSensorManager();



}

// Called just before this Command runs the first time
void SpinUpShooter::Initialize()
{
	pid = new PIDController(P, I, D, this,this);

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
double PIDSource::PIDGet(){
	return 0;
}
void PIDOutput::PIDWrite(float output){


}
