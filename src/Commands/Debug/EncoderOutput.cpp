#include "EncoderOutput.h"
#include <CommandBase.h>
#include <Subsystems/Drivebase.h>

EncoderOutput::EncoderOutput()
{
	sensorManager = SensorManager::getSensorManager();
}

// Called just before this Command runs the first time
void EncoderOutput::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void EncoderOutput::Execute()
{
	SmartDashboard::PutNumber("Left Encoder Ticks", CommandBase::drivebase->getLeftDistance()-SmartDashboard::GetNumber("curLeftOffset", 0));
	SmartDashboard::PutNumber("Right Encoder Ticks", CommandBase::drivebase->getRightDistance()-SmartDashboard::GetNumber("curRightOffset", 0));
}

// Make this return true when this Command no longer needs to run execute()
bool EncoderOutput::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void EncoderOutput::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void EncoderOutput::Interrupted()
{

}
