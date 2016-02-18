#include <Commands/Driving/DriveForward.h>
#include <math.h>
#include <RobotMap.h>
#include <Subsystems/Drivebase.h>

DriveForward::DriveForward(float distance, float speed)
{
	Requires(drivebase);
	WHEEL_DIAMETER = 8;					//CHANGE (maybe)
	ENCODER_TICKS_PER_REVOLUTION = 1000;//CHANGE
	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
	this->distance = distance;
	this->speed = speed;
	initialYaw = 0.0;
	initialPosition = 0.0;
	errorOffset = 0.0;
}

DriveForward::~DriveForward()
{
}

void DriveForward::Initialize()
{
	initialYaw = sensorManager->getYaw();
	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);
	initialPosition = sensorManager->GetEncoderPosition(DRIVEBASE_LEFTMOTOR_1_PORT);
}

void DriveForward::Execute()
{
	errorOffset = initialYaw - sensorManager->getYaw();
	if(errorOffset <= 0) {
		drivebase->setLeftSpeed(speed);
		drivebase->setRightSpeed((-1*(1/15)*errorOffset + 1) * speed);
	} else if(errorOffset >= 0) {
		drivebase->setLeftSpeed(((1/15)*errorOffset + 1) * speed);
		drivebase->setRightSpeed(speed);
	}

}

bool DriveForward::IsFinished()
{

	if(sensorManager->GetEncoderPosition(DRIVEBASE_LEFTMOTOR_1_PORT)/(ENCODER_TICKS_PER_REVOLUTION) * (M_PI*WHEEL_DIAMETER) >= distance) {
		return true;
	}
	return false;

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
