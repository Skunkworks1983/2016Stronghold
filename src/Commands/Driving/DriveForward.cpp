#include <Commands/Driving/DriveForward.h>
#include <RobotMap.h>
#include <Services/Logger.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <cstdio>

DriveForward::DriveForward(float distance, float speed) {
	Requires(drivebase);
	//WHEEL_DIAMETER = 8;					//CHANGE (maybe)
	//ENCODER_TICKS_PER_REVOLUTION = 1000;//CHANGE
	sensorManager = SensorManager::getSensorManager();
	motorManager = MotorManager::getMotorManager();
	this->distance = distance;
	this->speed = speed;
	initialYaw = 0.0;
	initialPosition = 0.0;
	errorOffset = 0.0;

	char str[1024];
	sprintf(str, "Inside DriveForward Constructor");
	writeToLogFile(LOGFILE_NAME, str);

	leftEncoder = SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID);
	rightEncoder = SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID);
}

DriveForward::~DriveForward() {
}

void DriveForward::Initialize() {
	initialYaw = sensorManager->getYaw();
	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);
	initialPosition = (leftEncoder->PIDGet() + rightEncoder->PIDGet()) / 2;
	char str[1024];
	sprintf(str, "DriveForward Initialize Called");
	writeToLogFile(LOGFILE_NAME, str);
}

void DriveForward::Execute() {
	/*errorOffset = initialYaw - sensorManager->getYaw();
	 if (errorOffset <= 0) { //If its tilting to the left
	 drivebase->setLeftSpeed(speed);
	 drivebase->setRightSpeed((-1 * (1 / 15) * errorOffset + 1) * speed); //At 15 degree error to the left, no forward motion, just pivot
	 } else if (errorOffset >= 0) { //If its tilting to the right
	 drivebase->setLeftSpeed(((1 / 15) * errorOffset + 1) * speed); //Same but tilted to the right
	 drivebase->setRightSpeed(speed);
	 }*/
	char str[1024];
	sprintf(str, "LeftEnc %f RightEnc %f",
			(double) SensorManager::getSensorManager()->getSensor(
			SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet(),
			(double) SensorManager::getSensorManager()->getSensor(
			SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());
	writeToLogFile(LOGFILE_NAME, str);
}

bool DriveForward::IsFinished() {
	if (((leftEncoder->PIDGet() + rightEncoder->PIDGet()) / 2) - initialPosition > distance) {
		return true;
	}/*
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
