#include "ResetEncoders.h"
#include <CommandBase.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Subsystems/Drivebase.h>

ResetEncoders::ResetEncoders()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void ResetEncoders::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ResetEncoders::Execute()
{
	SmartDashboard::PutNumber("curLeftOffset", CommandBase::drivebase->getLeftDistance());
	SmartDashboard::PutNumber("curRightOffset", CommandBase::drivebase->getRightDistance());
}

// Make this return true when this Command no longer needs to run execute()
bool ResetEncoders::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ResetEncoders::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetEncoders::Interrupted()
{

}
