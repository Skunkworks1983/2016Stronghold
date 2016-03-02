#include <Commands/Driving/RotateTowardCameraTarget.h>
#include <RobotMap.h>
#include <Services/CameraReader.h>
#include <Subsystems/Drivebase.h>
#include <cstdio>
#include <Services/Logger.h>

RotateTowardCameraTarget::RotateTowardCameraTarget() {
	Requires(drivebase);
	controller = new PIDController(MOVE_TOWARD_CAMERA_P, MOVE_TOWARD_CAMERA_I,
	MOVE_TOWARD_CAMERA_D, this, this);
	controller->SetInputRange(-1,1);
	lostTarget = false;
	outputspeed = 0;
	invalidCount = 0;
	error = 0;
}

RotateTowardCameraTarget::~RotateTowardCameraTarget() {
	delete controller;
}

void RotateTowardCameraTarget::Initialize() {
	CameraReader::getCameraReader()->startReading();
	controller->SetSetpoint(0.0);
	controller->Enable();
	lostTarget = false;
}

void RotateTowardCameraTarget::Execute() {
	//*twiddle thumbs*
	SmartDashboard::PutNumber("Error", error);
	SmartDashboard::PutNumber("output", outputspeed);
}

bool RotateTowardCameraTarget::IsFinished() {
	return lostTarget;
}

void RotateTowardCameraTarget::Interrupted() {
	End();
}

void RotateTowardCameraTarget::End() {
	controller->Disable();
	CameraReader::getCameraReader()->stopReading();
}

void RotateTowardCameraTarget::PIDWrite(float output) {
	if (CameraReader::getCameraReader()->getLastX() != INVALID) {
		int range = 1;
		if (output < -range || output > range) {
			//printf("Output outside of range !(%d < %f < %d)", -range, output, range);
			return;
		}

		outputspeed = output;
		drivebase->setLeftSpeed(output);
		drivebase->setRightSpeed(- output);
	}else{
		//printf("CAMERA READER READ IS INVALID\n");
		Logger::getLogger()->log("CAMERA READER READ IS INVALID", Info);
	}
}

double RotateTowardCameraTarget::PIDGet() {
	if (CameraReader::getCameraReader()->getLastX() == INVALID) {
		//printf("CAMERA READER READ IS INVALID\n");
		Logger::getLogger()->log("CAMERA READER READ IS INVALID", Info);
		//CameraReader::getCameraReader()->stopReading();
		if(invalidCount++ > 20){
			CameraReader::getCameraReader()->stopReading();
			controller->Disable();
			End();
		}
	}else{
		invalidCount = 0;
	}
	error = CameraReader::getCameraReader()->getLastX();
	return CameraReader::getCameraReader()->getLastX();
}
