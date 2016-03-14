#include <Commands/TimeOut.h>
#include <Services/Logger.h>
#include <cstdbool>
#include <cstdio>

TimeOut::TimeOut(float timeout) :timeout(timeout)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void TimeOut::Initialize()
{
	char str[1024];
		sprintf(str, "TimeOut started for %f seconds", timeout);
		Logger::getLogger()->log(str, Info);
	SetTimeout(timeout);
}

// Called repeatedly when this Command is scheduled to run
void TimeOut::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool TimeOut::IsFinished()
{
	return IsTimedOut();
}

// Called once after isFinished returns true
void TimeOut::End()
{
	char str[1024];
		sprintf(str, "Timeout Ended after %f seconds", timeout);
		Logger::getLogger()->log(str, Info);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TimeOut::Interrupted()
{

}
