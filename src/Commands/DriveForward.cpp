#include "DriveForward.h"

DriveForward::DriveForward(float distance, float speed, bool orient)
{
	Requires(drivebase);
	this->distance = distance;
	this->speed = speed;
}

DriveForward::~DriveForward()
{

}

void DriveForward::Initialize()
{
	drivebase->resetEncoder();
	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);
}

void DriveForward::Execute()
{

}

bool DriveForward::IsFinished()
{
	return (CommandBase::drivebase->getLeftDistance() >= distance
			&& CommandBase::drivebase->getRightDistance() >= distance);
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
