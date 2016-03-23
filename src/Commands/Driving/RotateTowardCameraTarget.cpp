#include <Commands/Driving/RotateTowardCameraTarget.h>
#include <RobotMap.h>
#include <Services/CameraReader.h>
#include <Services/Logger.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <cmath>

#define ERROR_TOLERANCE .1


/**
 * Rotate Robot toward camera target using PIDController
 */
RotateTowardCameraTarget::RotateTowardCameraTarget(float timeout) :
		timeout(timeout) {
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
	//only set timeout if larger than default value
	if (timeout > 0.0) {
		SetTimeout(timeout);
	}
	CameraReader::getCameraReader()->startReading();
	controller->SetSetpoint(0.0);
	controller->Enable();
}

void RotateTowardCameraTarget::Execute() {
	SmartDashboard::PutNumber("Error", error);
	SmartDashboard::PutNumber("output", outputspeed);
	//if last x value less than tolerance we are close to target
	if (fabs(CameraReader::getCameraReader()->getLastLeftX()) < ERROR_TOLERANCE) {
		onTargetCount++;
	} else {
		//"lost" target, reset
		onTargetCount = 0;
	}
}

bool RotateTowardCameraTarget::IsFinished() {
	//onTargetCount set in execute when target within tolerance
	return onTargetCount > 10 || IsTimedOut();
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
		outputspeed = output;
		//don't log on every tick
		if (PIDWriteCounter++ > 10) {
			LOG_INFO("CameraOutput %f", output);
			PIDWriteCounter = 0;
		}

		drivebase->setLeftSpeed(output);
		//reverse right side to turn
		drivebase->setRightSpeed(-output);
	} else {
		//don't log every tick
		if (PIDWriteCounter++ > 10) {
			LOG_WARNING("CAMERA READER READ IS INVALID");
			PIDWriteCounter = 0;
		}
	}
}
