#include <Commands/ZeroGyro.h>
#include <Services/SensorManager.h>
#include <cstdbool>

ZeroGyro::ZeroGyro()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void ZeroGyro::Initialize()
{
	SensorManager::getSensorManager()->ZeroYaw();
}

// Called repeatedly when this Command is scheduled to run
void ZeroGyro::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool ZeroGyro::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ZeroGyro::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ZeroGyro::Interrupted()
{

}
