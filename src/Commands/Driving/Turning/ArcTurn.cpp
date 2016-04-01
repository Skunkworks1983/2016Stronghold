#include <Commands/Driving/Turning/ArcTurn.h>
#include <Services/MotorManager.h>
#include <Services/Sensor.h>
#include <Services/SensorManager.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <RobotMap.h>
#include <cmath>

#define TURN_DEGREE_ESPSILON 2.0

ArcTurn::ArcTurn(double targetDegrees, double speed, double percentTurn,
		bool absolute) :
		targetDegrees(targetDegrees), speed(speed), percentTurn(percentTurn), absolute(
				absolute) {
	Requires(drivebase);
}

// Called just before this Command runs the first time
void ArcTurn::Initialize() {
	motorManger = MotorManager::getMotorManager();
	sensorManager = SensorManager::getSensorManager();

	initialLeft = fabs(sensorManager->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	initialRight = fabs(sensorManager->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	initialYaw = sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();

	if (!absolute) {
		if (sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet() + targetDegrees
				> 180.0) {
			targetDegrees += sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();
			targetDegrees -= 180.0;
			targetDegrees *= -1;
		} else if (sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet()
				+ targetDegrees < -180.0) {
			targetDegrees += sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();
			targetDegrees += 180.0;
			targetDegrees *= -1;
		} else {
			targetDegrees += sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();
		}
	}else{
		LOG_INFO("ArcTurn is absolute with target %f", targetDegrees);
	}

	LOG_INFO("ArcTurn starting with target %f speed %f yaw %f", targetDegrees,
			speed, sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet());

}

// Called repeatedly when this Command is scheduled to run
void ArcTurn::Execute() {
	double leftEncoder =
			fabs(
					sensorManager->getSensor(SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	double rightEncoder =
			fabs(
					sensorManager->getSensor(SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());
	const double yaw = sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();
	const double error = yaw - targetDegrees;

	const double P = 1 / 90;

	//speed -= error * P;

	LOG_INFO("target %f error %f speed %f", targetDegrees, error, speed);

	if (error > 0) {
		drivebase->setLeftSpeed(speed);
		drivebase->setRightSpeed(speed * percentTurn);
	} else {
		drivebase->setLeftSpeed(speed * percentTurn);
		drivebase->setRightSpeed(speed);
	}

}

// Make this return true when this Command no longer needs to run execute()
bool ArcTurn::IsFinished() {
	/*double leftEncoder = fabs(sensorManager->getSensor(
	 SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	 double rightEncoder = fabs(sensorManager->getSensor(
	 SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	 const bool leftPast = fabs(leftEncoder - initialLeft) > leftDist;
	 const bool rightPast = fabs(rightEncoder - initialRight) > rightDist;


	 return leftPast && rightPast;*/

	const double yaw = sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet();

	return fabs(yaw - initialYaw) > fabs(targetDegrees - initialYaw);

	if (targetDegrees > 0) {
		return yaw > targetDegrees;
	} else {
		return yaw < targetDegrees;
	}

	if (fabs(yaw - targetDegrees) < TURN_DEGREE_ESPSILON) {
		onCount++;
	} else {
		onCount = 0;
	}
	return onCount > 20;
}

// Called once after isFinished returns true
void ArcTurn::End() {
	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);

	LOG_INFO("ARC TURN ENDED WITH TARGET %f CURRENT YAW %f", targetDegrees,
			sensorManager->getSensor(SENSOR_GYRO_ID)->PIDGet());
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArcTurn::Interrupted() {
	End();
}