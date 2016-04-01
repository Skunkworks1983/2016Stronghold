#include <Commands/Driving/DriveForwardStraight.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <cstdio>
#include <cmath>

DriveForwardStraight::DriveForwardStraight(float distance, float speed) {
	Requires(drivebase);
	sensorManager = SensorManager::getSensorManager();
	this->distance = ((distance / DISTANCE_NUMBER));
	this->speed = speed;
	initialYaw = 0.0;
	initialPosition = 0.0;
	initialLeft = 0.0;
	initialRight = 0.0;
	error = 0.0;
}

DriveForwardStraight::~DriveForwardStraight() {
}

void DriveForwardStraight::Initialize() {
	initialYaw = sensorManager->getYaw();

	speed *= 12.75 / DriverStation::GetInstance().GetBatteryVoltage();

	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);

	initialLeft = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	initialRight = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	LOG_INFO("Using gyro for straight drive");
}

void DriveForwardStraight::Execute() {
	error = initialYaw - sensorManager->getYaw();
	double leftSpeed = ((1 / 15) * error + 1) * speed;
	double rightSpeed = (-1 * (1 / 15) * error + 1) * speed;
	LOG_INFO("Gyro: %f, Left: %f, Right: %f", sensorManager->getYaw(),
			leftSpeed, rightSpeed);
	const double P = .07;
	drivebase->setLeftSpeed(speed + error * P);
	drivebase->setRightSpeed(speed - error * P);

	/*if (error <= 0) { //If its tilting to the left
	 drivebase->setLeftSpeed(speed);
	 drivebase->setRightSpeed(rightSpeed); //At 15 degree error to the left, no forward motion, just pivot
	 } else if (error >= 0) { //If its tilting to the right
	 drivebase->setLeftSpeed(leftSpeed); //Same but tilted to the right
	 drivebase->setRightSpeed(speed);
	 }*/
}

bool DriveForwardStraight::IsFinished() {
	double left = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	double right = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	bool leftPast = fabs(left - initialLeft) > fabs(distance);
	bool rightPast = fabs(right - initialRight) > fabs(distance);

	return leftPast || rightPast;
}

void DriveForwardStraight::End() {
	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);
}

void DriveForwardStraight::Interrupted() {
	End();
}
