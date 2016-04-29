#include <Commands/Driving/AutoDriving/MoveBackUntilRoll.h>
#include <RobotMap.h>
#include <Services/SensorManager.h>
#include <Subsystems/Drivebase.h>

#define ON_ANGLE -3.75

MoveBackUntilRoll::MoveBackUntilRoll(double timeout) : timeout(timeout)
{
	Requires(drivebase);
}

// Called just before this Command runs the first time
void MoveBackUntilRoll::Initialize()
{
	const double speed = .25;
	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);
	if(timeout > 0){
		SetTimeout(timeout);
	}

	LOG_INFO("MoveBackUntilRoll has started with speed %f timeout %f", speed, timeout);

	if(SensorManager::getSensorManager()->getRoll() < -3.5){
		ready = false;
	}
}

// Called repeatedly when this Command is scheduled to run
void MoveBackUntilRoll::Execute()
{
	if(SensorManager::getSensorManager()->getRoll() > -1.25 && SensorManager::getSensorManager()->getRoll() < 1.25){
		ready = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool MoveBackUntilRoll::IsFinished()
{
	const double roll = SensorManager::getSensorManager()->getRoll();
	if(ready && roll < ON_ANGLE){
		count++;
	}else{
		count = 0;
	}

	LOG_INFO("MoveBackUntilRoll Roll %f count %u TimedOut %u", SensorManager::getSensorManager()->getRoll(), count, IsTimedOut());

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
