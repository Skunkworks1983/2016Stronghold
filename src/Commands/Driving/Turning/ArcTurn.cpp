#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/Turning/ArcTurn.h>
#include <RobotMap.h>
#include <Services/MotorManager.h>
#include <Services/Sensor.h>
#include <Services/SensorManager.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <cmath>

ArcTurn::ArcTurn(TurnData *d) {
	targetDegrees = d->angle;
	targetInput = targetDegrees;
	speed = d->power;
	originalSpeed = speed;
	percentTurn = d->percentage;
	Requires(drivebase);
}

ArcTurn::ArcTurn(double targetDegrees, double speed, double percentTurn,
bool absolute) :
		targetDegrees(-targetDegrees), speed(speed), percentTurn(percentTurn), absolute(
				absolute) {
	Requires(drivebase);
	targetInput = this->targetDegrees;
	originalSpeed = speed;
}

// Called just before this Command runs the first time
void ArcTurn::Initialize() {
	//SensorManager::getSensorManager()->ZeroYaw();

	motorManger = MotorManager::getMotorManager();
	sensorManager = SensorManager::getSensorManager();

	initialLeft = fabs(sensorManager->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	initialRight = fabs(sensorManager->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	initialYaw = sensorManager->getAngle();

	if (!absolute) {
		//nothing
	} else {
		targetDegrees -= initialYaw;

		LOG_INFO("ArcTurn is absolute with target %f", targetDegrees);
	}

	LOG_INFO("ArcTurn starting with target %f speed %f yaw %f", targetDegrees,
			speed, initialYaw);

}

// Called repeatedly when this Command is scheduled to run
void ArcTurn::Execute() {
	double yaw = sensorManager->getAngle();

	LOG_INFO("ArcTurn target %f yaw %f speed %f", targetDegrees, yaw, speed);

	// positive is clockwise on gyro heading
	if (targetDegrees < 0) {
		if (speed > 0) {
			drivebase->setLeftSpeed(speed * percentTurn); // * percentTurn slows it down
			drivebase->setRightSpeed(speed);
		} else {
			drivebase->setLeftSpeed(speed);
			drivebase->setRightSpeed(speed * percentTurn);
		}
	} else {
		if (speed > 0) {
			drivebase->setLeftSpeed(speed);
			drivebase->setRightSpeed(speed * percentTurn);
		} else {
			drivebase->setLeftSpeed(speed * percentTurn);
			drivebase->setRightSpeed(speed);
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ArcTurn::IsFinished() {
	double yaw = sensorManager->getAngle();

	if (fabs(yaw - targetDegrees) < 10) {
		speed = originalSpeed * .75;
	}

	//past and same sign
	return (fabs(yaw) > fabs(targetDegrees))
			&& (yaw < 0 ? -1 : 1) == (targetDegrees < 0 ? -1 : 1);
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
