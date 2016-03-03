#include <Commands/Driving/RotateTowardCameraTarget.h>
#include <RobotMap.h>
#include <Services/CameraReader.h>
#include <Subsystems/Drivebase.h>
#include <cstdio>
#include <Services/Logger.h>

#define ERROR_TOLERANCE .1

RotateTowardCameraTarget::RotateTowardCameraTarget() {
	Requires(drivebase);
	controller = new PIDController(MOVE_TOWARD_CAMERA_P, MOVE_TOWARD_CAMERA_I,
	MOVE_TOWARD_CAMERA_D, CameraReader::getCameraReader(), this);
	controller->SetInputRange(-1,1);
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
}

void RotateTowardCameraTarget::Execute() {
	//*twiddle thumbs*
	SmartDashboard::PutNumber("Error", error);
	SmartDashboard::PutNumber("output", outputspeed);
}

bool RotateTowardCameraTarget::IsFinished() {
	return fabs(controller->GetError()) < ERROR_TOLERANCE;
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
		drivebase->setLeftSpeed(output);
		drivebase->setRightSpeed(- output);
	}else{
		//printf("CAMERA READER READ IS INVALID\n");
		writeToLogFile(LOGFILE_NAME, "CAMERA READER READ IS INVALID");
	}
}
