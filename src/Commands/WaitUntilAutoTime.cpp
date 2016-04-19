#include <Commands/WaitUntilAutoTime.h>
#include <Robot.h>
#include <Utility.h>
#include <cstdbool>

WaitUntilAutoTime::WaitUntilAutoTime(double secondsIntoAuto) :
		secondsIntoAuto(secondsIntoAuto) {

}

// Called just before this Command runs the first time
void WaitUntilAutoTime::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void WaitUntilAutoTime::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool WaitUntilAutoTime::IsFinished() {
	return GetFPGATime() - Robot::getAutoStartTime()
			> secondsIntoAuto * 1000 * 1000;
}

// Called once after isFinished returns true
void WaitUntilAutoTime::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WaitUntilAutoTime::Interrupted() {

}
