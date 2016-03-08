#include <Commands/Driving/DriveForwardStraight.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <cstdio>
#include <cmath>

DriveForwardStraight::DriveForwardStraight(float distance, float speed) {
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
		char str[1024];
		sprintf(str, "DriveForward Initialize Called initialLeft %f initialRight %f ", initialLeft, initialRight);
		Logger::getLogger()->log(str, Info);
	}
}

void DriveForwardStraight::Execute() {
	if(USE_GYRO_TURN) {
		errorOffset = initialYaw - sensorManager->getYaw();
		int leftSpeed = ((1 / 15) * errorOffset + 1) * speed;
		int rightSpeed = (-1 * (1 / 15) * errorOffset + 1) * speed;
		char str[1024];
		sprintf(str, "Gyro: %i, Left: %f, Right: %f", sensorManager->getYaw(), leftSpeed, rightSpeed);
		Logger::getLogger()->log(str, Info);
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
		//drivebase->setRightSpeed(speed);
		drivebase->setRightSpeed(rightSpeed);

		char str[1024];
		sprintf(str, "left: %f, right: %f", left, right);
		Logger::getLogger()->log(str, Info);
	}
}

bool DriveForwardStraight::IsFinished() {
	double left = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	double right = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	double difference = ((left + right) / 2) - initialPosition;
	char str[1024];
	sprintf(str, "Difference: %f, target: %f", difference, distance);
	Logger::getLogger()->log(str, Info);
	if (difference > distance && !CONTINUOUS_TEST) { //Temp constant for testing if the gyro straight works
		return true;
	}
	/*if (((leftEncoder->PIDGet() + rightEncoder->PIDGet()) / 2) - initialPosition
	 > distance) {
	 return true;
	 }*/
	/*
	 if (sensorManager->GetEncoderPosition(DRIVEBASE_LEFTMOTOR_1_PORT)
	 >= distance) {
	 //PID drivebase back to error of 0 (not yet implemented, waiting on MotorManager updates)
	 return true;
	 }*/
	return false;
}

void DriveForwardStraight::End() {
	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);
}

void DriveForwardStraight::Interrupted() {
	End();
}
