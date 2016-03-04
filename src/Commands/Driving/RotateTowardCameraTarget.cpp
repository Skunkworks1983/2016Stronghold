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
}

RotateTowardCameraTarget::~RotateTowardCameraTarget() {
	delete controller;
}

void RotateTowardCameraTarget::Initialize() {
	CameraReader::getCameraReader()->startReading();
	controller->SetSetpoint(0.0);
	controller->Enable();

	double initialLeft = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	double initialRight = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	initialPosition = (initialLeft + initialRight) / 2;

}

void RotateTowardCameraTarget::Execute() {
	SmartDashboard::PutNumber("Error", error);
	SmartDashboard::PutNumber("output", outputspeed);
}

bool RotateTowardCameraTarget::IsFinished() {
	double left = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	double right = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	double difference = ((left + right) / 2) - initialPosition;

	if (distance > 0) {
		return fabs(difference) < distance;
	}
	if (speedTranslate == 0) {
		return fabs(controller->GetError()) < ERROR_TOLERANCE;
	}
	return false;
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
		drivebase->setLeftSpeed(speedTranslate + output);
		drivebase->setRightSpeed(speedTranslate - output);
	} else {
		//printf("CAMERA READER READ IS INVALID\n");
		writeToLogFile(LOGFILE_NAME, "CAMERA READER READ IS INVALID");
	}
}
