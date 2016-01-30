#include "DriveForward.h"
#include <Subsystems/SensorManager.h>
DriveForward::DriveForward(float distance, float speed, bool orient)
{
	Requires(drivebase);
	sensorManager = SensorManager::getSensorManager();
	this->distance = distance;
	this->speed = speed;
	startedCorrection = false;
	newYaw = 0.0;
	initialYaw = 0.0;
}

DriveForward::~DriveForward()
{

}

void DriveForward::Initialize()
{
	initialYaw = sensorManager->getYaw();
	drivebase->resetEncoder();
	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);
}

void DriveForward::Execute()
{

}

bool DriveForward::IsFinished()
{
	newYaw = sensorManager->getYaw();
	if(startedCorrection) {
		//Initialize PID and set variables
	}
	else if(CommandBase::drivebase->getLeftDistance() >= distance
			&& CommandBase::drivebase->getRightDistance() >= distance
			&& initialYaw != newYaw) {
		startedCorrection = true;
		//check PID, if within acceptable range return true
		if(false) { //Replace false with acceptable range calculation (or the result of said calculation)
			return true;
		} else { return false; }
	}
	return false;
	/*return (CommandBase::drivebase->getLeftDistance() >= distance
			&& CommandBase::drivebase->getRightDistance() >= distance);*/
}

void DriveForward::End()
{
	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);
}

void DriveForward::Interrupted()
{
	End();
}
