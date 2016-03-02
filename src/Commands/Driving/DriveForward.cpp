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
}

DriveForward::~DriveForward() {
}

void DriveForward::Initialize() {

	//initialYaw = sensorManager->getYaw();
	//drivebase->setLeftSpeed(speed);
	//drivebase->setRightSpeed(speed);
	initialLeft = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	initialRight = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	initialPosition = (initialLeft + initialRight) / 2;
	char str[1024];
	sprintf(str, "DriveForward Initialize Called");
	writeToLogFile(LOGFILE_NAME, str);
}

void DriveForward::Execute() {
	double left = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet() - initialLeft) + 1;
	double right = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet() - initialRight) + 1;

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
	/*errorOffset = initialYaw - sensorManager->getYaw();
	 if (errorOffset <= 0) { //If its tilting to the left
	 drivebase->setLeftSpeed(speed);
	 drivebase->setRightSpeed((-1 * (1 / 15) * errorOffset + 1) * speed); //At 15 degree error to the left, no forward motion, just pivot
	 } else if (errorOffset >= 0) { //If its tilting to the right
	 drivebase->setLeftSpeed(((1 / 15) * errorOffset + 1) * speed); //Same but tilted to the right
	 drivebase->setRightSpeed(speed);
	 }*/
	char str[1024];
	sprintf(str, "left: %f, right: %f", left, right);
	writeToLogFile(LOGFILE_NAME, str);
}

bool DriveForward::IsFinished() {
	double left = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	double right = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	double difference = ((left + right) / 2) - initialPosition;
	char str[1024];
	sprintf(str, "Difference: %f, Distance: %f", difference, distance);
	writeToLogFile(LOGFILE_NAME, str);
	if (difference > distance) {
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

void DriveForward::End() {
	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);
}

void DriveForward::Interrupted() {
	End();
}
