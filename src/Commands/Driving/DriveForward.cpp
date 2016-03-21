#include <Commands/Driving/DriveForward.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <cstdio>
#include <cmath>

DriveForward::DriveForward(float distance, float speed) {
	Requires(drivebase);
	//WHEEL_DIAMETER = 8;					//CHANGE (maybe)
	//ENCODER_TICKS_PER_REVOLUTION = 1000;//CHANGE
	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
	this->distance = ((distance / DISTANCE_NUMBER));
	this->speed = speed;
	initialYaw = 0.0;
	initialPosition = 0.0;
	errorOffset = 0.0;
	initialRight = 0.0;
	initialLeft = 0.0;
}

DriveForward::~DriveForward() {
}

void DriveForward::Initialize() {
	initialLeft = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	initialRight = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	LOG_INFO("DriveForward Initialize Called initialLeft %f initialRight %f ",
			initialLeft, initialRight);
}

void DriveForward::Execute() {
	double left = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet() - initialLeft);
	double right = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet() - initialRight);

	drivebase->setLeftSpeed(speed * 1.01);
	drivebase->setRightSpeed(speed);
}

bool DriveForward::IsFinished() {
	double left = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	double right = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	bool leftPast = fabs(left - initialLeft) > fabs(distance);
	bool rightPast = fabs(right - initialRight) > fabs(distance);

	return leftPast || rightPast;
}

void DriveForward::End() {
	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);
}

void DriveForward::Interrupted() {
	End();
}
