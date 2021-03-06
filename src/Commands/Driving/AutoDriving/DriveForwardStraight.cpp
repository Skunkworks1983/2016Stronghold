#include <Commands/Autonomous/AutoBase.h>
#include <Commands/Driving/AutoDriving/DriveForwardStraight.h>
#include <DriverStation.h>
#include <RobotMap.h>
#include <Services/Sensor.h>
#include <Subsystems/Drivebase.h>
#include <TuningValues.h>
#include <cmath>

DriveForwardStraight::DriveForwardStraight(float distance, float speed,
		double timeout, bool absolute) :
		timeout(timeout), absolute(absolute) {
	Requires(drivebase);
	sensorManager = SensorManager::getSensorManager();
	this->distance = ((distance / DRIVEBASE_FOOT_PER_TICK));
	this->speed = speed;
	initialYaw = 0.0;
	initialPosition = 0.0;
	initialLeft = 0.0;
	initialRight = 0.0;
	error = 0.0;
}

DriveForwardStraight::~DriveForwardStraight() {
}

void DriveForwardStraight::Initialize() {
//	SensorManager::getSensorManager()->ZeroYaw();

	if (timeout > 0) {
		SetTimeout(timeout);
	}
	if (absolute) {
		if (AutoBase::getObstacle() != Obstacle_cheval) {
			initialYaw = 0.0;
		} else {
			initialYaw = 180.0;
		}
	} else {
		initialYaw = sensorManager->getAngle();
	}

	speed *= 12.75 / DriverStation::GetInstance().GetBatteryVoltage();

	drivebase->setLeftSpeed(speed);
	drivebase->setRightSpeed(speed);

	initialLeft = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	initialRight = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	LOG_INFO("StraightDrive target %f initial yaw %f initialLeft %f initialRight %f ", distance * DRIVEBASE_FOOT_PER_TICK,
			initialYaw, initialLeft, initialRight);
}

void DriveForwardStraight::Execute() {
	error = initialYaw - sensorManager->getAngle();

	if (error < -180.0) {
		error += 360.0;
	} else if (error > 180.0) {
		error -= 360.0;
	}

	const double P = .07;
	drivebase->setLeftSpeed(speed + error * P);
	drivebase->setRightSpeed(speed - error * P);
}

bool DriveForwardStraight::IsFinished() {
	double left = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_LEFT_ENCODER_ID)->PIDGet());
	double right = fabs(SensorManager::getSensorManager()->getSensor(
	SENSOR_DRIVE_BASE_RIGHT_ENCODER_ID)->PIDGet());

	LOG_INFO(
			"StraightDrive Error %f LeftEncoder %f rightEncoder %f distance %f",
			error, left, right, distance)

	bool leftPast = fabs(left - initialLeft) > fabs(distance);
	bool rightPast = fabs(right - initialRight) > fabs(distance);

	return leftPast || rightPast || IsTimedOut();
}

void DriveForwardStraight::End() {
	drivebase->setLeftSpeed(0);
	drivebase->setRightSpeed(0);
}

void DriveForwardStraight::Interrupted() {
	End();
}
