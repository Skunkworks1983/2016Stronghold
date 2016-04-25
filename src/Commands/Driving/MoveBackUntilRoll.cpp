#include <Commands/Driving/MoveBackUntilRoll.h>
#include <Services/SensorManager.h>
#include <Subsystems/Drivebase.h>
#include <RobotMap.h>

#define ON_ANGLE -3.5

MoveBackUntilRoll::MoveBackUntilRoll(double timeout) : timeout(timeout)
{
	Requires(drivebase);
}

// Called just before this Command runs the first time
void MoveBackUntilRoll::Initialize()
{
	drivebase->setLeftSpeed(.5);
	drivebase->setRightSpeed(.5);
	if(timeout > 0){
		SetTimeout(timeout);
	}
}

// Called repeatedly when this Command is scheduled to run
void MoveBackUntilRoll::Execute()
{
	LOG_INFO("Current Roll %f", SensorManager::getSensorManager()->getRoll());
}

// Make this return true when this Command no longer needs to run execute()
bool MoveBackUntilRoll::IsFinished()
{
	const double roll = SensorManager::getSensorManager()->getRoll();
	if(roll < ON_ANGLE){
		count++;
	}else{
		count = 0;
	}
	return count > 15 || IsTimedOut();
}

// Called once after isFinished returns true
void MoveBackUntilRoll::End()
{
	drivebase->setLeftSpeed(0.0);
	drivebase->setRightSpeed(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveBackUntilRoll::Interrupted()
{
	End();
}
