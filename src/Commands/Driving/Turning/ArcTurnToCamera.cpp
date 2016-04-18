#include <Commands/Driving/Turning/ArcTurnToCamera.h>
#include <RobotMap.h>
#include <Services/CameraReader.h>
#include <Services/MotorManager.h>
#include <Services/Sensor.h>
#include <Services/SensorManager.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <cmath>

ArcTurnToCamera::ArcTurnToCamera(double speed, double percentTurn,
		double timeout) :
		speed(speed), percentTurn(percentTurn), timeout(timeout) {
	Requires(drivebase);
}

// Called just before this Command runs the first time
void ArcTurnToCamera::Initialize() {
	if (targetDegrees == 0.0) {
		targetDegrees = .001;	//LOLOL
	}

	//targetDegrees = CameraReader::getCameraReader()->getCorrectedXAngle();
	targetDegrees = CameraReader::getCameraReader()->getXAngle();
	targetInput = targetDegrees;

	if(targetDegrees == INVALID){
		invalidCamera = true;
	}

	motorManger = MotorManager::getMotorManager();
	sensorManager = SensorManager::getSensorManager();

	initialLeft = fabs(sensorManager->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	initialRight = fabs(sensorManager->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	initialYaw = sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();

	if (sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet() + targetDegrees
			> 180.0) {
		targetDegrees += sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();
		targetDegrees -= 360.0;
	} else if (sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet()
			+ targetDegrees < -180.0) {
		targetDegrees += sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();
		targetDegrees += 360.0;
	} else {
		targetDegrees += sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();
	}

	LOG_INFO("ArcTurnToCamera starting with target %f speed %f yaw %f", targetDegrees,
			speed, initialYaw);
}

// Called repeatedly when this Command is scheduled to run
void ArcTurnToCamera::Execute() {
	if (targetInput > 0) {
		if (speed > 0) {
			drivebase->setLeftSpeed(speed);
			drivebase->setRightSpeed(speed * percentTurn);
		} else {
			drivebase->setLeftSpeed(speed * percentTurn);
			drivebase->setRightSpeed(speed);
		}
	} else {
		if (speed > 0) {
			drivebase->setLeftSpeed(speed * percentTurn);
			drivebase->setRightSpeed(speed);
		} else {
			drivebase->setLeftSpeed(speed);
			drivebase->setRightSpeed(speed * percentTurn);
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ArcTurnToCamera::IsFinished() {
	if(invalidCamera){
		return true;
	}

	double yaw = sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();

	LOG_INFO("ArcTurnToCameraIsFinished Yaw %f Target %f", yaw, targetDegrees);

	if (targetInput < 0) {
		if (speed < 0) {
			return yaw < targetDegrees
					&& (yaw / fabs(yaw))
							== (targetDegrees / fabs(targetDegrees));
		} else {
			return yaw < targetDegrees
					&& (yaw / fabs(yaw))
							== (targetDegrees / fabs(targetDegrees));
		}
	} else {
		if (speed < 0) {
			return yaw > targetDegrees
					&& (yaw / fabs(yaw))
							== (targetDegrees / fabs(targetDegrees));
		} else {
			return yaw > targetDegrees
					&& (yaw / fabs(yaw))
							== (targetDegrees / fabs(targetDegrees));
		}
	}

	return false;
}

// Called once after isFinished returns true
void ArcTurnToCamera::End() {
	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);

	LOG_INFO("ARC TURN ENDED WITH TARGET %f CURRENT YAW %f", targetDegrees,
			sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet());
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArcTurnToCamera::Interrupted() {
	End();
}
