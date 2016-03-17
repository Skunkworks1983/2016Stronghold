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
	motorManager = MotorManager::getMotorManager();
	this->distance = ((distance / DISTANCE_NUMBER));
	this->speed = speed;
	initialYaw = 0.0;
	initialPosition = 0.0;
	initialLeft = 0.0;
	initialRight = 0.0;
	errorOffset = 0.0;
}

DriveForwardStraight::~DriveForwardStraight() {
}

void DriveForwardStraight::Initialize() {
	if(USE_GYRO_TURN) {
		initialYaw = SensorManager::getSensorManager()->getYaw();
		drivebase->setLeftSpeed(speed);
		drivebase->setRightSpeed(speed);
		Logger::getLogger()->log("Using gyro for straight drive", Info);
	} else {
		initialLeft = fabs(SensorManager::getSensorManager()->getSensor(
		SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
		initialRight = fabs(SensorManager::getSensorManager()->getSensor(
		SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

		initialPosition = (initialLeft + initialRight) / 2;
		LOG_INFO("DriveForward Initialize Called initialLeft %f initialRight %f ", initialLeft, initialRight);
	}
}

void DriveForwardStraight::Execute() {
	if(USE_GYRO_TURN) {
		errorOffset = initialYaw - sensorManager->getYaw();
		double leftSpeed = ((1 / 15) * errorOffset + 1) * speed;
		double rightSpeed = (-1 * (1 / 15) * errorOffset + 1) * speed;
		LOG_INFO("Gyro: %f, Left: %f, Right: %f", sensorManager->getYaw(), leftSpeed, rightSpeed);
		 if (errorOffset <= 0) { //If its tilting to the left
			 drivebase->setLeftSpeed(speed);
			 drivebase->setRightSpeed(rightSpeed); //At 15 degree error to the left, no forward motion, just pivot
		 } else if (errorOffset >= 0) { //If its tilting to the right
			 drivebase->setLeftSpeed(leftSpeed); //Same but tilted to the right
			 drivebase->setRightSpeed(speed);
		 }
	} else {
		double left = fabs(SensorManager::getSensorManager()->getSensor(
		SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet() - initialLeft);
		double right = fabs(SensorManager::getSensorManager()->getSensor(
		SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet() - initialRight);

		// Ignore for first ticks
		left = left > 200 ? left : 200;
		right = right > 200 ? right : 200;

		//double leftSpeed = speed * (pow(right, 2) / pow(left,2));
		double leftSpeed = speed * (right / left);

		//double rightSpeed = speed * (pow(left,2) / pow(right,2));
		double rightSpeed = speed * (left / right);
		drivebase->setLeftSpeed(leftSpeed);
		drivebase->setRightSpeed(rightSpeed);

		LOG_INFO("left: %f, right: %f", left, right);
	}
}

bool DriveForwardStraight::IsFinished() {
	double left = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	double right = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	double difference = ((left + right) / 2) - initialPosition;
	LOG_INFO("Difference: %f, target: %f", difference, distance);
	if (difference > distance && !CONTINUOUS_TEST) { //Temp constant for testing if the gyro straight works
		return true;
	}
	return false;
}

void DriveForwardStraight::End() {
	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);
}

void DriveForwardStraight::Interrupted() {
	End();
}
