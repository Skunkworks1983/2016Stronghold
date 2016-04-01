#include <Commands/Climbing/StopArmPID.h>
#include <Services/MotorManager.h>
#include <TuningValues.h>

StopArmPID::StopArmPID()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void StopArmPID::Initialize()
{
	MotorManager::getMotorManager()->disablePID(PID_ID_ARM);
}

// Called repeatedly when this Command is scheduled to run
void StopArmPID::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool StopArmPID::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void StopArmPID::End()
{
	MotorManager::getMotorManager()->disablePID(PID_ID_ARM);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopArmPID::Interrupted()
{

}
