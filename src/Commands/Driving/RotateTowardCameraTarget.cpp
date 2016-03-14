#include <Commands/Driving/RotateTowardCameraTarget.h>
#include <RobotMap.h>
#include <Services/CameraReader.h>
#include <Services/Logger.h>
#include <Services/SensorManager.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <cmath>

#define ERROR_TOLERANCE .1

RotateTowardCameraTarget::RotateTowardCameraTarget(float speedTranslate,
		float distance) :
		speedTranslate(speedTranslate), distance(distance) {
	Requires(drivebase);
	controller = new PIDController(MOVE_TOWARD_CAMERA_P, MOVE_TOWARD_CAMERA_I,
	MOVE_TOWARD_CAMERA_D, CameraReader::getCameraReader(), this);
	controller->SetInputRange(-1, 1);
	outputspeed = 0;
	error = 0;
	initialRight = 0.0;
	initialLeft = 0.0;
}

RotateTowardCameraTarget::~RotateTowardCameraTarget() {
	delete controller;
}

void RotateTowardCameraTarget::Initialize() {
	CameraReader::getCameraReader()->startReading();
	controller->SetSetpoint(0.0);
	controller->Enable();

	initialLeft = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	initialRight = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	initialPosition = (initialLeft + initialRight) / 2;

}

void RotateTowardCameraTarget::Execute() {
	SmartDashboard::PutNumber("Error", error);
	SmartDashboard::PutNumber("output", outputspeed);
}

bool RotateTowardCameraTarget::IsFinished() {
//	double left = fabs(SensorManager::getSensorManager()->getSensor(
//	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
//	double right = fabs(SensorManager::getSensorManager()->getSensor(
//	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());
//
//	double difference = ((left + right) / 2) - initialPosition;
//
//	if (distance > 0) {
//		return fabs(difference) < distance;
//	}
//	if (speedTranslate == 0) {
//		return fabs(controller->GetError()) < ERROR_TOLERANCE;
//	}
//	return false;
	double left = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	double right = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	bool leftPast = fabs(left - initialLeft) > fabs(distance);
	bool rightPast = fabs(right - initialRight) > fabs(distance);

	return leftPast || rightPast;
}

void RotateTowardCameraTarget::Interrupted() {
	End();
}

void RotateTowardCameraTarget::End() {
	controller->Disable();
	CameraReader::getCameraReader()->stopReading();
}

void RotateTowardCameraTarget::PIDWrite(float output) {
	if (!CameraReader::getCameraReader()->isLastInvalid()) {
		int range = 1;
		if (output < -range || output > range) {
			return;
		}

		outputspeed = output;
		char str[1024];
		sprintf(str, "CameraOutput %f", output);
		Logger::getLogger()->log(str, Info);
		drivebase->setLeftSpeed(speedTranslate + output);
		drivebase->setRightSpeed(speedTranslate - output);
	} else {
		Logger::getLogger()->log("CAMERA READER READ IS INVALID", Info);
	}
}
