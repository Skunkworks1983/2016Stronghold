#include <Commands/Shooting/SpinUpShooter.h>
#include <OI.h>
#include <Services/MotorManager.h>
#include <Services/SensorManager.h>
<<<<<<< HEAD:src/Commands/Shooting/SpinUpShooter.cpp

SpinUpShooter::SpinUpShooter()
=======
//
SpinUpShooter::SpinUpShooter(float timeOut, float speed)
>>>>>>> refs/remotes/origin/collector:src/Commands/SpinUpShooter.cpp
{

	oi = new OI();
	motorManager = MotorManager::getMotorManager();
	sensorManager = SensorManager::getSensorManager();
<<<<<<< HEAD:src/Commands/Shooting/SpinUpShooter.cpp
=======
	this->timeOut = timeOut;



>>>>>>> refs/remotes/origin/collector:src/Commands/SpinUpShooter.cpp
}

// Called just before this Command runs the first time
void SpinUpShooter::Initialize()
{
<<<<<<< HEAD:src/Commands/Shooting/SpinUpShooter.cpp

=======
>>>>>>> refs/remotes/origin/collector:src/Commands/SpinUpShooter.cpp

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
